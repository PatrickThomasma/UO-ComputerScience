/*Authorship
 * Name: Patrick Thomasma
 * DuckID: 951623133
 * Duckmail: pthomasm@uoregon.edu
 * Project: CIS 415 Project 2: Pthread based packet driver
 * Statement: This is my own work, with assitance from timmy
*/


#include <stdlib.h>
#include "diagnostics.h"
#include "destination.h"
#include "BoundedBuffer.h"
#include "fakeapplications.h"
#include "freepacketdescriptorstore__full.h"
#include "freepacketdescriptorstore.h"
#include "networkdevice.h"
#include "networkdevice__full.h"
#include "packetdriver.h"
#include "packetdescriptorcreator.h"
#include "packetdescriptor.h"
#include "pid.h"
#include "queue.h"
#include <pthread.h>
#define ATTEMPTS 10
#define UNUSED __attribute__((unused)) 
//2 could maybe work but probably better if its slightly higher?
//Want to do global variables for initializing the buffer 
//establish bounded buffers which Joe has defined for us
//bounded buffers are queues for the packets to be sent and received
//Joe made the thread sync so we don't have to worry about unlocking and locking

//Maybe make a struct


/*Just helperfunctions
 *
 */

/*void init_packet_driver Can pick an arbitrary size
 * creating free packet descriptor
 * create any buffers for threads
 * create any therads you require for implementation
 * return FPDS to code that called you
 *
*/

/*void blocking_send_packet
 * queue up packet descriptor for sending
 * do not return until it has been succesfully queued 
 * */

/*int nonblocking_send_packet
 * if you are able to queue then do so and return 1
 * other return 0 */

/*void blocking_get_packet
 * wait until there is packet for pid
 * return packet descriptor to call application */

/*nonblocking_get_packet
 * if there is currently a waiting packet for pid, return that packet
 * to calling applicationa nd return 1 for value of function
 * otherwise return 0 for value of the function
 */
static BoundedBuffer *buffer[MAX_PID + 1];
static BoundedBuffer *pendingsendbuffer;
static BoundedBuffer *buffpool;
static NetworkDevice *network;
static FreePacketDescriptorStore *store;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t get = PTHREAD_COND_INITIALIZER;
//pthread_cond_t send = PTHREAD_COND_INITIALIZER;
pthread_t senderthread; 
pthread_t receivethread;

static void *sender(UNUSED void *args) {
	PacketDescriptor *packet;
	int send_status;
	while (1) {
		//get packet from the receive buffer
		if (pendingsendbuffer->nonblockingRead(pendingsendbuffer, (void **)&packet) != 1)
			pendingsendbuffer->blockingRead(pendingsendbuffer, (void **)&packet);

                //try to signal the network to send this packet
		for (int i = 0; i < ATTEMPTS; i++) {
			if((send_status = network->sendPacket(network, packet)) == 1) {
				DIAGNOSTICS("[DRIVER> Info: Sent a packet after %d tries\n", i + 1);
				break;
			} 
		}
		//if packet has not been sent after 10 tries then report it
		if (send_status == 0) {
			DIAGNOSTICS("[DRIVER> Info: Failed to send a packet after %d tries\n", ATTEMPTS);
		}
		//put packet back into the store
		if (store->nonblockingPut(store, packet) != 1)
			store->blockingPut(store, packet);
	}
	return NULL;
}

static int nonblockingGet(PacketDescriptor *packet) {
	int status;
	//try and grab from the pool, if we can't then we will pull from the store
	if (!(status = buffpool->nonblockingRead(buffpool, (void **) &packet) ) == 0)
		status = store->nonblockingGet(store,&packet);
	return status;
}

static int nonblockingPut(PacketDescriptor *packet) {
	int status;
	//write into the pool, if we can't then write into the store
	if (!(status = buffpool->nonblockingWrite(buffpool, (void **) &packet))) {
		status = store->nonblockingPut(store,packet);
	}
	return status;
}

static void *receiver(UNUSED void *args) {
//making two packets to differentiate between where we're pulling form
	PacketDescriptor *packet;
	PacketDescriptor *oldpacket;
	PID pid;
	//initially we will grab from the store
        if (store->nonblockingGet(store, &packet) != 1)
		store->blockingGet(store, &packet);
	initPD(packet);

	//DIAGNOSTICS ("[DRIVER> INFO: REGISTER 1");
	network->registerPD(network,packet);
	while (1) {
		network->awaitIncomingPacket(network);
		oldpacket = packet;
		//try and get from the pool, if we don't grab from pool then we are grabbing from network
		if (nonblockingGet(packet)) {
			initPD(packet);
	//		DIAGNOSTICS ("[DRIVER> INFO: REGISTER 2");
			network->registerPD(network,packet);

			//network->awaitIncomingPacket(network);
			pid = getPID(oldpacket);
			DIAGNOSTICS("[DRIVER> Info: Packet received for application %u\n", pid);
			//try to write into the buffer processes, if we can't do that then we will try to write into the pool and failing that we will put the packet back into the store
			if (!(buffer[pid]->nonblockingWrite(buffer[pid], (void *) packet))) {
				if (!nonblockingPut(oldpacket))
					DIAGNOSTICS("[DRIVER> Info: Warning, Packet cannot be returned to the store\n");
			}
		} else {
			//if we have grabbed from the pool then we will have to do less work since information will already be in that packet.
			packet = oldpacket;
			initPD(packet);
	//		DIAGNOSTICS ("[DRIVER> INFO: REGISTER 3");
			network->registerPD(network,packet);
		}
	}
	return NULL;

}
//pending will remain same size
//receiver will remain same size
//sending buffer size doesn't change but initial size will be different number based on different packets, will want to know size of receiver, keep track of how many processes that we're working with, keep track of buffer size for each of the pending buffers. The relationship of these 4 will be size of the senidng
//Buffer is related to Amount of procesees, sending buffer, receiving buffer
void init_packet_driver(NetworkDevice *nd, void *mem_start, unsigned long mem_length, FreePacketDescriptorStore **fpds) {
	unsigned long fpds_size;
	*fpds = FreePacketDescriptorStore_create(mem_start, mem_length);
	fpds_size = (*fpds)->size(*fpds);
	network = nd;
	store = *fpds;
	PacketDescriptor *packet;
	//PacketDescriptor *pd = create_free_packet_descriptor(*fpds,mem_start,mem_length)
	for (int i = 0; i < MAX_PID + 1; i++) {
		//create size two for process buffers so we can fit two processes in one buffer potentially
		if ((buffer[i] = BoundedBuffer_create(2)) == NULL) {
			fpds_size -= 2;
			DIAGNOSTICS("Error creating BB");
		}
	}
	//initializing size to be 22 so later we can divive by 2 between the two buffer pools
	fpds_size -= (MAX_PID + 1) * 2;
	if ((pendingsendbuffer = BoundedBuffer_create(fpds_size / 2)) == NULL) {
		DIAGNOSTICS("Error creating BB");
	}
	buffpool = BoundedBuffer_create(fpds_size / 2);

	//Take a couple of stuff from store and put into the pool first thing.
	for (int i = 0; i < (int)((fpds_size / 2) - 2); i++) {
		store->blockingGet(store, &packet);
		buffpool->blockingWrite(buffpool, (void *) packet);
	}
//	nd->awaitIncomingPacket(nd);
	if (pthread_create(&senderthread, NULL,  sender, NULL))
		DIAGNOSTICS ("Failed to create send thread");
	if(pthread_create(&receivethread, NULL , receiver,NULL))
		DIAGNOSTICS ("Failed to create receive thread");

}

void blocking_send_packet(PacketDescriptor *pd) { //basically one line
	pendingsendbuffer->blockingWrite(pendingsendbuffer, (void *) pd);
	


}

//Just invoke a method he gave us to put packetdescriptor into the buffer

int nonblocking_send_packet(PacketDescriptor *pd) { //basically one line
	int succ = pendingsendbuffer->nonblockingWrite(pendingsendbuffer, (void*) pd);
	if (succ)
		return 1;
	return 0;

}

void blocking_get_packet(PacketDescriptor **pd, PID pid) { //basically one line

	buffer[pid]->blockingRead(buffer[pid], (void **) pd);
}

int nonblocking_get_packet(PacketDescriptor **pd, PID pid) { //basically one line
	int succ = buffer[pid]->nonblockingRead(buffer[pid], (void **)pd);
	if (succ) 
		return 1;
	return 0;



}

/* Notes from Lecture 11, Hints on Project 2 
 * What are we asked to do?
 * Building a packet driver that is part of the kernel
 * implement one function that the kernel bootstrap calls [init_packet_driver()]
 * Implement two system calls that permit an application to sned a packet on the network [blocking_send_packet() and nonblocking_send_packet()]
 * Implement two system calls that permit an application to retrieve a packet from the network [blocking_get_packet()] and nonblocking_get_packet()
 * network device can only transmit one packet onto network at a time
 * Simultaneously, the network device can receive one packet from the network at a time
 * May define any required global data, threads, and synchronization mechanisms needed to handle the mismatch between application requests and interaction with the network
 * FreePacketDescriptorStore
 * All interactions with packet driver are in terms of PacketDescriptors(PDs)
 * The kernel bootstrap provides a fixed amount of memory from which you are to construct the store in the initialization
 * An application that wants to send a packet on the network has to retrieve a PD from the store and fill it in, then pass to driver by calling one of the send system calls
 * Send system calls must queue up these PDs, and other logic in your driver must retrieve one PD at a time from the queue, and request the network driver to transmit the packet on the network.
 * After packet has been transmitted, this logic must return PD to the store.
 * In order to read messages from network, logic in driver must retreieve a PD from the store, initialize the PD, register it with network driver, and then wait for that PD to be filled in with a network message.
 * Upon receipt of a packet, the PD must be queued for receipt by the destination application.
 * An application that wants to receive a packet from network that was targeted at applications calls one of your get() system calls
 * System call logic must be able to pass least recently received PD for that application back through a system call argument.
 * Application is required to return that PD to the store when done with it
 * Facts about networking:
 * Protocols are built over raw packet transmission
 * Lost packets are a natural occurance at the lowest level, 
 * physical medium (packet collisions on a shared medium)
 * external influences (cosmic rays)
 * Buffer overflows
 * Protocols must maintain higher level connectivity despite lost packets
*/

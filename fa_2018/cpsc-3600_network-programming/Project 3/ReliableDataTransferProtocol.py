# Dylan Mumm
# CPSC 3600
# Project 3
# # Implements a Reliable Data Transfer Protocol


from Simulator import Simulator
from Simulator import Packet
from Simulator import EventEntity
from enum import Enum


class ReliableDataTransferProtocol():
    def __init__(self, bidirectional = False):
        self.bidirectional = bidirectional
        self.simulator = None


    # This routine will be called once, before any of your other A-side routines are called.
    # It can be used to do any required initialization.
    def A_Init(self):

        self.stateA = StateS.WAIT_FOR_0_CALL
        self.packetBufferA = Packet()


    # This routine will be called whenever the upper layer at the sending side (A) has a message to send.
    # It is the job of your protocol to insure that the data in such a message is delivered in-order,
    # and correctly, to the receiving side upper layer.

    def A_CommunicateWithApplicationLayer(self, message):

        self.simulator.trace("A received {} from application layer".format(message),1)

        if self.stateA == StateS.WAIT_FOR_0_CALL:

            send          = Packet()
            send.seqnum   = 0
            send.payload  = message
            send.checksum = self.findChecksum(send)

            self.packetBufferA = send
            self.simulator.to_layer3(EventEntity.A, send)
            self.simulator.start_timer(EventEntity.A, 20)
            self.stateA = StateS.WAIT_FOR_0_ACK

        elif self.stateA == StateS.WAIT_FOR_1_CALL:

            send = Packet()
            send.seqnum = 1
            send.payload = message
            send.checksum = self.findChecksum(send)

            self.packetBufferA = send
            self.simulator.to_layer3(EventEntity.A, send)
            self.simulator.start_timer(EventEntity.A, 20)
            self.stateA = StateS.WAIT_FOR_1_ACK

        else: pass


    # This routine will be called whenever a packet sent from the B-side (i.e., as a result of a tolayer3()
    # being done by a B-side procedure) arrives at the A-side. packet is the (possibly corrupted) packet
    # sent from the B-side.
    def A_CommunicateWithNetworkLayer(self, packet):

        self.simulator.trace("A received a packet (SEQ: {}, ACK: {}, Checksum: {}, Payload: {}) from network layer layer".format(
            packet.seqnum, packet.acknum, packet.checksum, packet.payload), 1)

        if self.stateA == StateS.WAIT_FOR_0_ACK:
            if packet.acknum == 1 or packet.checksum != self.findChecksum(packet): pass
            else:
                self.simulator.stop_timer(EventEntity.A)
                self.stateA = StateS.WAIT_FOR_1_CALL
        elif self.stateA == StateS.WAIT_FOR_1_ACK:
            if packet.acknum == 0 or packet.checksum != self.findChecksum(packet): pass
            else:
                self.simulator.stop_timer(EventEntity.A)
                self.stateA = StateS.WAIT_FOR_0_CALL

        else: pass





    # This routine will be called when A's timer expires (thus generating a timer interrupt). You'll probably
    # want to use this routine to control the retransmission of packets. See starttimer() and stoptimer()
    # below for how the timer is started and stopped.
    def A_TimerInterrupt(self):

        self.simulator.trace("A: Timer Interrupt", 1)
        self.simulator.to_layer3(EventEntity.A, self.packetBufferA)
        self.simulator.start_timer(EventEntity.A, 20)

    # This routine will be called once, before any of your other B-side routines are called.
    # It can be used to do any required initialization.
    def B_Init(self):

        self.stateB = StateR.WAIT_FOR_0_SEQ


    # This routine will be called whenever a packet sent from the A-side (i.e., as a result of a tolayer3() being done
    # by a A-side procedure) arrives at the B-side. packet is the (possibly corrupted) packet sent from the A-side.
    def B_CommunicateWithNetworkLayer(self, packet):

        self.simulator.trace("B received a packet (SEQ: {}, ACK: {}, Checksum: {}, Payload: {}) from network layer layer".format(
            packet.seqnum, packet.acknum, packet.checksum, packet.payload), 1)

        if self.stateB == StateR.WAIT_FOR_0_SEQ:
            if packet.seqnum == 1 or packet.checksum != self.findChecksum(packet):
                send = Packet()
                send.acknum   = 1
                send.checksum = self.findChecksum(send)
                self.simulator.to_layer3(EventEntity.B, send)
            else:
                send          = Packet()
                send.acknum   = 0
                send.checksum = self.findChecksum(send)
                self.simulator.to_layer3(EventEntity.B, send)
                self.stateB   = StateR.WAIT_FOR_1_SEQ

        elif self.stateB == StateR.WAIT_FOR_1_SEQ:
            if packet.seqnum == 0 or packet.checksum != self.findChecksum(packet):
                send          = Packet()
                send.acknum   = 0
                send.checksum = self.findChecksum(send)
                self.simulator.to_layer3(EventEntity.B, send)
            else:
                self.simulator.to_layer3(EventEntity.B, packet)
                send          = Packet()
                send.acknum   = 1
                send.checksum = self.findChecksum(send)
                self.simulator.to_layer3(EventEntity.B, send)
                self.stateB   = StateR.WAIT_FOR_1_SEQ

    def findChecksum(self, packet):
        return packet.seqnum + packet.acknum + sum(ord(c) for c in packet.payload)

class StateS(Enum):

    WAIT_FOR_0_CALL = 0
    WAIT_FOR_0_ACK = 1
    WAIT_FOR_1_CALL = 4
    WAIT_FOR_1_ACK = 3

class StateR(Enum):

    WAIT_FOR_0_SEQ = 0
    WAIT_FOR_1_SEQ = 1



if __name__ == "__main__":
    rdt = ReliableDataTransferProtocol()
    simulator = Simulator(rdt)

    simulator.Setup()
    simulator.Simulate()
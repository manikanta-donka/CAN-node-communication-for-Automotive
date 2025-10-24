# CAN-node-communication-for-Automotive

Introduction
The idea of microcontroller CAN bus project is a vehicle bus standard designed to allow Microcontrollers and devices to communicate with each other in applications without a host computer. It is a message-based protocol, designed originally for multiplex electrical wiring within auto-mobiles, but is also used in many other contexts. CAN is an electronic communication bus defined by the ISO 11898 standards. Those standards define how communication happens, how wiring is configured and how messages are constructed, among other things. Collectively, this system is referred to as a CAN bus.

The CAN is a broadcast bus, which means that all nodes can ‘hear’ all transmissions. There is no way to send a message to just a specific node connected via the bus. All nodes will pick up all the data transmitted in the bus. The CAN hardware, however, provides local filtering so that each node may react only on the interesting messages. CAN uses short messages with maximum utility load is 94 bits. There is no explicit address in the messages. Instead, the messages can be said to be contents-addressed, that is, their contents implicitly determines their address. There are four type of messages sent in form of frames, namely:

Data Frame – The Data Frame is the most common message type for data exchange
Remote Frame – It is used to solicit the transmission of corresponding Data Frame
Error Frame – The Error Frame is a special message that violates the framing rules
Overload Frame – Overload frame is transmitted by a node that becomes too busy
Along with this the CAN protocol has multiple other features like Bus Arbitration and Message Priority, Message Addressing and Identification and Error Handling.

The goal of microcontroller CAN bus project is to implement CAN protocol based data exchange between two PIC based boards, which are acting as “nodes”. In this implementation automotive use-case is assumed by exchanging data like engine temperature, speed etc. that are displayed using LCD panels.

Requirement Details
Default Screen
The system should display the current system parameters.
Mode Selection
By pressing the MODE key the display should toggle between Operation Mode and Config Mode
Config Mode
Set Node ID
Press CF key to enter this screen
The default Node ID should be displayed
UP / DOWN key is used to change the node ID
ACK key updates the Node ID and stores it in persistent memory
Return to the Config Screen
Set Thresholds
Press CF key to enter this screen
UP / DOWN key to scroll the menu
ACK key should be used to select the parameter to be changed
UP / DOWN key is used to change the parameter
ACK key updates the changes in persistent memory
Return to the Config Screen
Operation Mode
On request from the server, the system parameters should be transferred to the server
On exceeding the set parameter threshold, a message should be sent to the server

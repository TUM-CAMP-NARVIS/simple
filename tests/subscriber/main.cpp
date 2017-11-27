#include <signal.h>
#include <fstream>
#include <iostream>
#include <string>
#include "subscriber.h"
#include "generic_message.h"
#include "header.h"

static int s_interrupted = 0;
static void s_signal_handler(int signal_value) { s_interrupted = 1; }

static void s_catch_signals(void) {
	signal(SIGINT, s_signal_handler);
	signal(SIGTERM, s_signal_handler);
}

int main(int argc, char* argv[]) {

	// create subscriber context
	simple::Subscriber<simple_msgs::HeaderFbs>::context_ = zmq::context_t(1);

	// create the subscriber

	simple::Subscriber<simple_msgs::HeaderFbs> sub("tcp://localhost:5555");

	// create the holder for the incoming data
	//simple_msgs::HeaderFbs h(0, "", 0.0);
	
	s_catch_signals();
	while (!s_interrupted) {
		try {
			//receive message and print the content
			auto h = sub.subscribe();
			std::cout << "Received sequence number: " << h->sequence_number() << std::endl;
			std::cout << "Received frame id: " << h->frame_id() << std::endl;
			std::cout << "Received time stamp: " << h->timestamp()<< std::endl;

		}

		catch (zmq::error_t& e) {
			std::cout << "Something went wrong with the subscription"
				<< "\n";
		}
	}

	std::cout << "Interruption received"
		<< "\n";
	//close the context
	simple::Subscriber<simple_msgs::HeaderFbs>::context_.close();

	return 0;
}


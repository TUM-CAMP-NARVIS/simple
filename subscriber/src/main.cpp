#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <signal.h>
#include "SIMPLE.pb.h"
#include "Subscriber.h"
#include <google/protobuf/text_format.h>
#include "myContext.h"

static int s_interrupted = 0;
static void s_signal_handler(int signal_value)
{
  s_interrupted = 1;
}

static void s_catch_signals(void)
{
  signal(SIGINT, s_signal_handler);
  signal(SIGTERM, s_signal_handler);
}

int main(int argc, char* argv[])
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  // create context
  simple::myContext globalContext;

  // create one type of subscriber for each message type, for testing

  simple::Subscriber<SIMPLE::CAPABILITY> subCap("tcp://localhost:5555", *globalContext.context);
  simple::Subscriber<SIMPLE::TRANSFORM> subTrans("tcp://localhost:5556", *globalContext.context);
  simple::Subscriber<SIMPLE::POSITION> subPos("tcp://localhost:5557", *globalContext.context);
  simple::Subscriber<SIMPLE::STATUS> subStat("tcp://localhost:5558", *globalContext.context);
  simple::Subscriber<SIMPLE::GENERIC> subGen("tcp://localhost:5559", *globalContext.context);

  // create the holders for the incoming data

  std::vector<std::string> Capabilities;
  SIMPLE::HEADER CapHeader;

  SIMPLE::HEADER TransHeader;
  double px, py, pz, r11, r12, r13, r21, r22, r23, r31, r32, r33;

  SIMPLE::HEADER PosHeader;
  double pospx, pospy, pospz, e1, e2, e3, e4;

  SIMPLE::HEADER StatHeader;
  int code, subcode;
  std::string errorName, errorMsg;

  SIMPLE::HEADER GenHeader;
  bool data;

  s_catch_signals();
  while (true)
  {
    try
    {
		std::unique_ptr<SIMPLE::CAPABILITY> recvCap = subCap.subscribe();
		subCap.readMsg(*recvCap, CapHeader, Capabilities);

		std::unique_ptr<SIMPLE::TRANSFORM> recvTrans = subTrans.subscribe();
		subTrans.readMsg(*recvTrans, TransHeader, px, py, pz, r11, r12, r13, r21, r22, r23, r31, r32, r33);

		std::unique_ptr<SIMPLE::POSITION> recvPos = subPos.subscribe();
		subPos.readMsg(*recvPos, PosHeader, pospx, pospy, pospz, e1, e2, e3, e4);

		std::unique_ptr<SIMPLE::STATUS> recvStat = subStat.subscribe();
		subStat.readMsg(*recvStat, StatHeader, code, subcode, errorName, errorMsg);

		std::unique_ptr<SIMPLE::GENERIC> recvGen = subGen.subscribe();
		subGen.readMsg(*recvGen, GenHeader, data);
    }

    catch (zmq::error_t& e)
    {
      std::cout << "Something went wrong with the subscription"
                << "\n";
    }

	//print the received data
	std::cout << "Capability received: " << Capabilities.at(0) << ", " << Capabilities.at(1) << ", " << Capabilities.at(2) << "\n";
	std::cout << "Transform received: px=" << px << ", py=" << py << ", pz=" << pz << ", r11=" << r11 << "\n";
	std::cout << "Position received: px=" << pospx << ", py=" << pospy << ", pz=" << pospz << ", e1=" << e1 << ", e2=" << e2 << "\n";
	std::cout << "Status received: code=" << code << ", subcode=" << subcode << ", errorName=" << errorName << ", errorMsg=" << errorMsg << "\n";
	std::cout << "Generic received: bool=" << data << "\n";

    if (s_interrupted)
    {
      std::cout << "Interruption received"
                << "\n";
      break;
    }
  }

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}

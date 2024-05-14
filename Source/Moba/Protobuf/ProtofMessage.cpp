// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtofMessage.h"
//#include "Windows/AllowWindowsPlatformTypes.h"
#include "test.pb.h"
//#include "Windows/HideWindowsPlatformTypes.h"

ProtofMessage::ProtofMessage()
{
	test aa;

	aa.set_id(333);
	aa.set_greeting("aaaaaaa");
	std::string sss = aa.SerializeAsString();
	const char* a = sss.c_str();
}

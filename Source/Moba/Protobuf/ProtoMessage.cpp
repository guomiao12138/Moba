// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtoMessage.h"
//#include "Windows/AllowWindowsPlatformTypes.h"

//#include "Windows/HideWindowsPlatformTypes.h"

ProtoMessage::ProtoMessage()
{
	aa.set_id(333);
	aa.set_greeting("aaaaaaa");
	std::string sss = aa.SerializeAsString();
	const char* a = sss.c_str();
}

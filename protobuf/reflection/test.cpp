#include <stdio.h>
#include <iostream>
#include "test.pb.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"
#include "google/protobuf/compiler/importer.h"
#include "google/protobuf/dynamic_message.h"

int main()
{
//////////////////
	auto descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName("T.Test");
	if (descriptor == nullptr)
	{
		return 0;
	}

	auto prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
	if (prototype == nullptr)
	{
		return 0;
	}

	auto message = prototype->New();
	auto test_message = dynamic_cast<T::Test*>(message);
	test_message->set_id(111);
	std::cout << test_message->Utf8DebugString() << std::endl;
	delete message;

//////////////////
	T::Test p_test;
	auto m_descriptor = p_test.GetDescriptor();
	auto m_reflection = p_test.GetReflection();
	auto field = m_descriptor->FindFieldByName("id");
	m_reflection->SetInt32(&p_test, field, 5);
	std::cout << p_test.Utf8DebugString() << std::endl;

//////////////////
	google::protobuf::compiler::DiskSourceTree sourceTree;
	sourceTree.MapPath("project_root", "./");
	google::protobuf::compiler::Importer importer(&sourceTree, nullptr);
	importer.Import("project_root/test.proto");

	auto i_descriptor = importer.pool()->FindMessageTypeByName("T.Test");
	google::protobuf::DynamicMessageFactory factory;
	auto i_proto = factory.GetPrototype(i_descriptor);
	auto i_message = i_proto->New();
	auto i_reflection = i_message->GetReflection();
	auto i_field = i_descriptor->FindFieldByName("id");
	i_reflection->SetInt32(i_message, i_field, 10);
	std::cout << i_message->Utf8DebugString() << std::endl;
	return 0;
}

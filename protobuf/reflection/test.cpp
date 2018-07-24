#include <stdio.h>
#include <string.h>
#include <iostream>
#include "test.pb.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"
#include "google/protobuf/compiler/importer.h"
#include "google/protobuf/dynamic_message.h"

void serialize_message(const google::protobuf::Message& message, std::string* serialized_string) {
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::Reflection* reflection = message.GetReflection();

	for (int i = 0; i < descriptor->field_count(); ++i) {
		const google::protobuf::FieldDescriptor* field = descriptor->field(i);
		bool has_field = reflection->HasField(message, field);

		if (has_field) {
			//arrays not supported
			assert(!field->is_repeated());
			
			switch (field->cpp_type()) {
#define CASE_FIELD_TYPE(cpptype, method, valuetype) \
			case google::protobuf::FieldDescriptor::CPPTYPE_##cpptype:{ \
			valuetype value = reflection->Get##method(message, field); \
			int wsize = field->name().size(); \
			serialized_string->append(reinterpret_cast<char*>(&wsize), sizeof(wsize));\
			serialized_string->append(field->name().c_str(), field->name().size());\
			wsize = sizeof(value);\
			serialized_string->append(reinterpret_cast<char*>(&wsize), sizeof(wsize));\
			serialized_string->append(reinterpret_cast<char*>(&value), sizeof(value));\
			break;\
			}

			CASE_FIELD_TYPE(INT32, Int32, int);
			CASE_FIELD_TYPE(UINT32, UInt32, uint32_t);
			CASE_FIELD_TYPE(FLOAT, Float, float);
			CASE_FIELD_TYPE(DOUBLE, Double, double);
			CASE_FIELD_TYPE(BOOL, Bool, bool);
			CASE_FIELD_TYPE(INT64, Int64, int64_t);
			CASE_FIELD_TYPE(UINT64, UInt64, uint64_t);
#undef CASE_FIELD_TYPE
			case google::protobuf::FieldDescriptor::CPPTYPE_ENUM: {
			int value = reflection->GetEnum(message, field)->number();
			int wsize = field->name().size();
			//写入name占用字节数
			serialized_string->append(reinterpret_cast<char*>(&wsize), sizeof(wsize));
			//写入name
			serialized_string->append(field->name().c_str(), field->name().size());
			wsize = sizeof(value);
			//写入value占用字节数
			serialized_string->append(reinterpret_cast<char*>(&wsize), sizeof(wsize));
			//写入value
			serialized_string->append(reinterpret_cast<char*>(&value), sizeof(value));
			}
			break;
			case google::protobuf::FieldDescriptor::CPPTYPE_STRING: {
			std::string value = reflection->GetString(message, field);
			int wsize = field->name().size();
			serialized_string->append(reinterpret_cast<char*>(&wsize), sizeof(wsize));
			serialized_string->append(field->name().c_str(), field->name().size());
			wsize = value.size();
			serialized_string->append(reinterpret_cast<char*>(&wsize), sizeof(wsize));
			serialized_string->append(value.c_str(), value.size());
			}
			break;
			case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE: {
			std::string value;
			int wsize = field->name().size();
			serialized_string->append(reinterpret_cast<char*>(&wsize), sizeof(wsize));
			serialized_string->append(field->name().c_str(), field->name().size());
			const google::protobuf::Message& submessage = reflection->GetMessage(message, field);
			serialize_message(submessage, &value);
			wsize = value.size();
			serialized_string->append(reinterpret_cast<char*>(&wsize), sizeof(wsize));
			serialized_string->append(value.c_str(), value.size());
			}
			break;
			}
		}
	}
}

/*
void parse_message(const std::string& serialized_string, google::protobuf::Message* message) {
	const google::protobuf::Descriptor* descriptor = message->GetDescriptor();
	const google::protobuf::Reflection* reflection = message->GetReflection();
	std::map field_map;

	for (int i = 0; i field_count(); ++i) {
		const google::protobuf::FieldDescriptor* field = descriptor->field(i);
		field_map[field->name()] = field;
	}

	const google::protobuf::FieldDescriptor* field = NULL;
	size_t pos = 0;
	while (pos (serialized_string.substr(pos, sizeof(int)).c_str()));
	pos += sizeof(int);
	std::string name = serialized_string.substr(pos, name_size);
	pos += name_size;

	int value_size = *(reinterpret_cast(serialized_string.substr(pos, sizeof(int)).c_str()));
	pos += sizeof(int);
	std::string value = serialized_string.substr(pos, value_size);
	pos += value_size;

	std::map::iterator iter =
		field_map.find(name);
	if (iter == field_map.end()) {
		fprintf(stderr, "no field found.n");
		continue;
	} else {
		field = iter->second;
	}

	assert(!field->is_repeated());
	switch (field->cpp_type()) {
#define CASE_FIELD_TYPE(cpptype, method, valuetype) \
		case google::protobuf::FieldDescriptor::CPPTYPE_##cpptype: { \
			   reflection->Set##method(message, field, *(reinterpret_cast(value.c_str()))); \
			   std::cout name() (value.c_str())) enum_type()->FindValueByNumber(*(reinterpret_cast(value.c_str())));
										   reflection->SetEnum(message, field, enum_value_descriptor);
										   std::cout name() (value.c_str())) SetString(message, field, value);
										   std::cout name() MutableMessage(message, field);
										   parse_message(value, submessage);
										   break;
									   }
		default: {
				 break;
			 }
	}
}
}
*/

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

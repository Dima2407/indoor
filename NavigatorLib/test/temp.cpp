//
// Created by kyb on 21.03.17.
//

#include <iostream>
#include <cstdio>
#include <stdexcept>

#include "ItJim/JsonDataContract.h"

using namespace std;
using namespace rapidjson;
using namespace ItJim;

/*int main()
{
	FILE *fp = fopen("trace-20172402_063151.json", "rb");  // non-Windows use "r"
	std::vector<char> readBuffe(262144);
	rapidjson::FileReadStream is(fp, readBuffe.data(), readBuffe.capacity());
	Document doc;
	doc.ParseStream(is);  // after this
	assert(doc.IsArray());
	cout<<endl<<endl<<endl;
	int i=0;
	for (auto it=doc.Begin(); it!=doc.End(); ++it) {
		JsonDataContract::OutputPosition pos = JsonDataContract::OutputPosition::ParseDOM(it->GetObject());
		cout << i++ << " \t |" << pos.x << "|\t" << pos.y << "|\t" << pos.z << endl;
	}
	fclose(fp);
}*/


/*int main()
{
	FILE* fp = fopen("temp.json", "w"); // non-Windows use "w", Windows "w"
	std::vector<char> json_buf(262144);
	rapidjson::FileWriteStream  os (fp, json_buf.data(), json_buf.capacity());
	//char json_buf[262144];
	//rapidjson::FileWriteStream  os (fp, json_buf, 262144);
	rapidjson::Writer<rapidjson::FileWriteStream>  json_writer (os);
	
	rapidjson::Document doc(rapidjson::kArrayType);
	for(int i=1; i<10; i++){
		doc.PushBack(Value(i*2), doc.GetAllocator());
	}
	
	doc.Accept(json_writer);
	fclose(fp);
}*/


//int main()
//{
//	//using namespace JsonDataContract;
//	//using namespace Navigator::Beacons;
//
//	/*std::vector<JsonDataContract::BeaconReceivedDataJson> receivedBeaconPackets
//			{
//				 {1, "", "", 2.5, "AC:DE", "AC:DE:DE:AA:BB:00", 0, 57.8, 0, 78, 123456789}
//				,{1, "", "", 2.5, "AC:DE", "AC:DE:DE:AA:BB:00", 0, 57.8, 0, 78, 123456789}
//				,{1, "", "", 2.5, "AC:DE", "AC:DE:DE:AA:BB:00", 0, 57.8, 0, 78, 123456789}
//				,{1, "", "", 2.5, "AC:DE", "AC:DE:DE:AA:BB:00", 0, 57.8, 0, 78, 123456789}
//				,{1, "", "", 2.5, "AC:DE", "AC:DE:DE:AA:BB:00", 0, 57.8, 0, 78, 123456789}
//			};*/
//	std::vector<JsonDataContract::OutputPosition> positions = {
//			 JsonDataContract::OutputPosition{1,1,0}
//			,JsonDataContract::OutputPosition{2,2,0}
//			,JsonDataContract::OutputPosition{3,3,0}
//			,JsonDataContract::OutputPosition{4,4,0}
//			,JsonDataContract::OutputPosition{5,5,0}
//	};
//
//
//	FILE* fp = fopen("temp.json", "w"); // non-Windows use "w", Windows "w"
//	std::vector<char> json_buf(262144);
//	rapidjson::FileWriteStream  os (fp, json_buf.data(), json_buf.capacity());
//	rapidjson::PrettyWriter<rapidjson::FileWriteStream>  json_writer (os);
//	rapidjson::Document doc(rapidjson::kArrayType);
//
//	int i=0;
//	for (auto const& pos : positions) {
//		doc.PushBack( pos.toJson(doc), doc.GetAllocator() );
//		cout << i++ << " \t |" << pos.x << "|\t" << pos.y << "|\t" << pos.z << endl;
//		if( i>10 )
//			break;
//	}
//
//	doc.Accept(json_writer);
//	fclose(fp);
//}


/*int main()
{
	Document d(kObjectType);
	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	
	d.AddMember("x", Value(22), d.GetAllocator());
	d.AddMember("y", Value(23), d.GetAllocator());
	d.AddMember("x", Value(11), d.GetAllocator());
	d.AddMember("x", Value(nan("")), d.GetAllocator());
	d.AddMember("Z", Value(11), d.GetAllocator());
	
	d.Accept(writer);
	const char* output = buffer.GetString();
	printf("%s\n", output);
}*/


int main()
{
	cout << std::to_string(nan("")) << endl;
	cout << std::to_string(inf("")) << endl;
	cout << std::to_string(nan("")) << endl;
}

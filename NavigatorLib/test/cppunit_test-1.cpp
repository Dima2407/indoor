//
// Created by kyb on 15.03.17.
//


#include <iostream>
#include <cstdio>
#include <stdexcept>

#include "ItJim/JsonDataContract.h"
#include <cppunit/extensions/HelperMacros.h>

//using namespace CppUnit;
using namespace std;


namespace ItJim {

	class BeaconDataFilesTest : public CppUnit::TestCase
	{
		CPPUNIT_TEST_SUITE(BeaconDataFilesTest);
	
		CPPUNIT_TEST(test_20172402_063151);
		//CPPUNIT_TEST(test_20172402_063308);
		//CPPUNIT_TEST(testNothing);
	
		CPPUNIT_TEST_SUITE_END();
	
	public:
		void test_20172402_063151();
		
		void test_20172402_063308() {
			//CPPUNIT_ASSERT_EQUAL(2, 1);
		}
		
		void testNothing() {}
	};
	CPPUNIT_TEST_SUITE_REGISTRATION(BeaconDataFilesTest);
	
	
	//void BeaconDataFilesTest::test_20172402_063151()
	//{
	//	using namespace Navigator;
	//	using namespace Navigator::Beacons;
	//	using namespace Navigator::Beacons::Factory;
	//	using Navigator::Math::Position3D;
	//
	//	constexpr auto office_map_file = "beacons-data-files/premises-info/office-map.json";
	//	constexpr auto input_file = "beacons-data-files/2017-24-02_06-31-51_bluetooth.json";
	//	constexpr auto output_file = "trace-20172402_063151.json";
	//
	//	cout.precision(17);
	//
	//	// Create the Beacon Navigator
	//	TrilatBeaconNavigator navigator(
	//			/*rssiFact*/make_shared<AlphaBetaFilterFactory>(0.85, 0.005),
	//			/*distFact*/make_shared<AlphaBetaFilterFactory>(0.85, 0.005)
	//	);
	//
	//	// Read office map from .json to C++ struct
	//	auto map = JsonDataContract::ReadOfficeMap(office_map_file);
	//	cout << "List beacons from map:" << endl;
	//	cout << "| macAddress | x | y | z | TxPower | damp |" << endl;
	//	for (auto const& b : map->beacons) {
	//		cout << b.macAddress << " \t" << b.x << " \t" << b.y << " \t" << b.z << " \t" << b.txpower << " \t"
	//		     << b.damp << endl;
	//		// Add to Navigator
	//		navigator.addBeacon(
	//				Beacon(BeaconUID(b.macAddress), b.txpower, b.damp, Position3D(b.x, b.y, b.z))
	//		);
	//	}
	//
	//	auto receivedBeaconPackets = JsonDataContract::ReadSnifferedDataFromBeacons(input_file);
	//	cout << endl << "List received data from beacons:" << endl;
	//	cout << "| MACaddress | RSSI | Timestamp | TxPower | distance |" << endl;
	//	int i = 0;
	//	for (auto const & b : receivedBeaconPackets) {
	//		cout << i++ << " \t |" << b.MACaddress << " \t" << b.RSSI << " \t" << b.TimeStamp << " \t" << b.TXpower
	//		     << " \t" << b.distance << endl;
	//	}
	//
	//	rapidjson::Document doc(rapidjson::kArrayType);
	//	FILE* fp = fopen(output_file, "w"); // non-Windows use "w", Windows "w"
	//	std::vector<char> json_buf(262144);
	//	rapidjson::FileWriteStream  os (fp, json_buf.data(), json_buf.capacity());
	//	//char json_buf[262144];
	//	//rapidjson::FileWriteStream  os (fp, json_buf, 262144);
	//	rapidjson::PrettyWriter<rapidjson::FileWriteStream>  json_writer (os);
	//
	//	// Process every packet and write trace;
	//	cout << endl << "RESULT TRACE:" << endl;
	//	cout << "# \t | \t x \t | \t y \t |" << endl; //\t z \t |" << endl;
	//	cout.precision(2);
	//
	//	i=0;
	//	for (auto const& b : receivedBeaconPackets) {
	//		JsonDataContract::OutputPosition pos = navigator.process(
	//				BeaconReceivedData(b.TimeStamp, BeaconUID(b.MACaddress), b.RSSI)
	//		);
	//		doc.PushBack( pos.toJson(doc), doc.GetAllocator() );
	//		cout << i++ << " \t |" << pos.x << "|\t" << pos.y << "|\t" << pos.z << endl;
	//		if( i>10 )
	//			break;
	//	}
	//
	//	doc.Accept(json_writer);
	//	fclose(fp);
	//
	//	/*i = 0;
	//	for( auto it = doc.Begin(); it!=doc.End(); ++it ){
	//		//printf("asd");
	//		JsonDataContract::OutputPosition pos = JsonDataContract::OutputPosition::ParseDOM(it->GetObject());
	//		cout << i++ << " \t | " << pos.x << " | \t" << pos.y << " | \t" << pos.z << endl;
	//	}*/
	//
	//	fp = fopen(output_file, "rb");  // non-Windows use "r"
	//	std::vector<char> readBuffe(262144);
	//	rapidjson::FileReadStream is(fp, readBuffe.data(), readBuffe.capacity());
	//	doc.ParseStream(is);  // after this
	//	cout<<endl<<endl<<endl;
	//	i=0;
	//	for (auto it=doc.Begin(); it!=doc.End(); ++it) {
	//		JsonDataContract::OutputPosition pos = JsonDataContract::OutputPosition::ParseDOM(it->GetObject());
	//		cout << i++ << " \t |" << pos.x << "|\t" << pos.y << "|\t" << pos.z << endl;
	//	}
	//	fclose(fp);
	//}
	
	
	void BeaconDataFilesTest::test_20172402_063151()
	{
		using namespace Navigator;
		using namespace Navigator::Beacons;
		using namespace Navigator::Beacons::Factory;
		using Navigator::Math::Position3D;
		
		constexpr auto office_map_file = "beacons-data-files/premises-info/office-map.json";
		constexpr auto input_file = "beacons-data-files/2017-24-02_06-31-51_bluetooth.json";
		constexpr auto output_file = "trace-20172402_063151.json";
		
		cout.precision(17);
		
		// Create the Beacon Navigator
		TrilatBeaconNavigator navigator(
				/*rssiFact*/make_shared<AlphaBetaFilterFactory>(0.85, 0.005),
				/*distFact*/make_shared<AlphaBetaFilterFactory>(0.85, 0.005)
		);
		
		// Read office map from .json to C++ struct
		// Add beacons from map to navigator
		auto map = JsonDataContract::ReadOfficeMap(office_map_file);
		for (auto const& b : map->beacons) {
			navigator.addBeacon( b.toBeacon() );
		}
		
		rapidjson::Document doc(rapidjson::kArrayType);
		FILE* fp = fopen(output_file, "w"); // non-Windows use "w", Windows "w"
		std::vector<char> json_buf(262144);
		rapidjson::FileWriteStream  os (fp, json_buf.data(), json_buf.capacity());
		rapidjson::PrettyWriter<rapidjson::FileWriteStream>  json_writer (os);
		
		// Process every packet and write trace;
		cout << endl << "RESULT TRACE:" << endl;
		cout << "# \t | \t x \t | \t y \t |" << endl; //\t z \t |" << endl;
		cout.precision(2);
		
		auto receivedBeaconPackets = JsonDataContract::ReadSnifferedDataFromBeacons(input_file);
		int i=0;
		for (auto const& b : receivedBeaconPackets) {
			JsonDataContract::OutputPosition pos = navigator.process(
					BeaconReceivedData(b.TimeStamp, BeaconUID(b.MACaddress), b.RSSI)
			);
			if( pos.isFinite() ){
				rapidjson::Value pos_json = pos.toJson(doc);
				doc.PushBack(pos_json, doc.GetAllocator());
			}
			cout << i++ << " \t |" << pos.x << "|\t" << pos.y << "|\t" << pos.z << endl;
		}
		
		doc.Accept(json_writer);
		fclose(fp);
	}
		
} // namespace ItJim



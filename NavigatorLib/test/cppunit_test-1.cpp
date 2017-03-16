//
// Created by kyb on 15.03.17.
//

/*#include "teamcity-cpp/cppunit/teamcity_cppunit.h"

//#include "test1.h"


namespace Navigator {
	namespace Test {
		
		class test1
		{
			
		};
		
	}
}*/




#include <iostream>
//#include <cstdio>
#include <stdexcept>

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>

//#include "teamcity-cpp/cppunit/teamcity_cppunit.h"
#include "teamcity/teamcity_cppunit.h"

#include "rapidjson/rapidjson.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/error/en.h>
#include <algorithm>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "Navigator.h"


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


	
	using namespace rapidjson;
	
	/// Отражение того что дали It-Jim в своих json-файлах
	struct BeaconReceivedDataJson
	{
		int beaconTypeCode;
		std::string dataFields;
		std::string extraDataFields;
		double distance;  ///< большая погрешность
		std::string identifiers;
		std::string MACaddress;
		int manufacturer;
		double RSSI;
		int serviceUUID;
		double TXpower;
		double TimeStamp;
	
	public:
		static void CheckDOM(rapidjson::Document const& doc);
		static void ParseDOM(rapidjson::Value const& val, BeaconReceivedDataJson &to);
		static BeaconReceivedDataJson ParseDOM(rapidjson::Value const& val);
	
	public:
		bool operator<(BeaconReceivedDataJson const & other){
			return this->TimeStamp < other.TimeStamp;
		}
	};

	struct BeaconOnMapJson
	{
		double x;
		double y;
		double z;
		std::string macAddress;
		int major;
		int minor;
		double damp;
		double txpower;
		
	public:
		static void CheckDOM(rapidjson::Document const& doc);
		static void ParseDOM(rapidjson::Value const& val, BeaconOnMapJson &to);
		static BeaconOnMapJson ParseDOM(rapidjson::Value const& val);
	};
	
	/// Отражение того, что дали It-Jim в своих json-файлах
	struct MapJson
	{
		std::vector<BeaconOnMapJson> beacons;
		std::string description; //i.e. "Floor 1"
		double width;
		double height;
		double pixelSize;
		std::string path;
		std::string maskPath;
		std::string mapUid;
		std::string name;
	
	public:
		static void CheckDOM(rapidjson::Document const& doc);
		static void ParseDOM(rapidjson::Value const& val, MapJson &to);
		static MapJson ParseDOM(rapidjson::Value const& val);
	};
	
	
	
	void BeaconReceivedDataJson::CheckDOM(rapidjson::Document const& doc)
	{
		CPPUNIT_ASSERT( doc.IsArray() );
		CPPUNIT_ASSERT( doc[0].IsArray() );
		rapidjson::Value const& obj = doc[0][0];
		CPPUNIT_ASSERT( obj.IsObject() );
		CPPUNIT_ASSERT( obj.HasMember("beaconTypeCode") );
		CPPUNIT_ASSERT( obj["beaconTypeCode"].IsNumber() );
		CPPUNIT_ASSERT( obj.HasMember("dataFields") );
		CPPUNIT_ASSERT( obj.HasMember("extraDataFields") );
		CPPUNIT_ASSERT( obj.HasMember("distance") );
		CPPUNIT_ASSERT( obj.HasMember("identifiers") );
		CPPUNIT_ASSERT( obj.HasMember("MACaddress") );
		CPPUNIT_ASSERT( obj.HasMember("manufacturer") );
		CPPUNIT_ASSERT( obj.HasMember("RSSI") );
		CPPUNIT_ASSERT( obj.HasMember("serviceUUID") );
		CPPUNIT_ASSERT( obj.HasMember("TXpower") );
		CPPUNIT_ASSERT( obj.HasMember("TimeStamp") );
	}
	
	void BeaconReceivedDataJson::ParseDOM(rapidjson::Value const& val, BeaconReceivedDataJson &to)
	{
		to.beaconTypeCode = val["beaconTypeCode"].Get<int>();
		to.dataFields = val["dataFields"].GetString();
		to.extraDataFields = val["extraDataFields"].GetString();
		to.distance = val["distance"].Get<double>();
		to.identifiers = val["identifiers"].GetString();
		to.MACaddress = val["MACaddress"].GetString();
		to.manufacturer = val["manufacturer"].Get<int>();
		to.RSSI = val["RSSI"].Get<double>();
		to.serviceUUID = val["serviceUUID"].Get<int>();
		to.TXpower = val["TXpower"].Get<double>();
		to.TimeStamp = val["TimeStamp"].Get<double>();
	}
	
	BeaconReceivedDataJson BeaconReceivedDataJson::ParseDOM(rapidjson::Value const& val)
	{
		BeaconReceivedDataJson to;
		ParseDOM(val,to);
		return to;
	}
	
	
	
	
	//todo  void BeaconOnMapJson::CheckDOM(rapidjson::Document const& doc);
	
	void BeaconOnMapJson::ParseDOM(rapidjson::Value const& val, BeaconOnMapJson &to)
	{
		to.x = val["x"].Get<double>();
		to.y = val["y"].Get<double>();
		to.z = val["z"].Get<double>();
		to.macAddress = val["macAddress"].GetString();
		to.major = val["major"].Get<int>();
		to.minor = val["minor"].Get<int>();
		to.damp = val["damp"].Get<double>();
		to.txpower = val["txpower"].Get<double>();
	}
	
	BeaconOnMapJson BeaconOnMapJson::ParseDOM(rapidjson::Value const& val)
	{
		BeaconOnMapJson to;
		ParseDOM(val,to);
		return to;
	}
	
	
	
	//todo void MapJson::CheckDOM(rapidjson::Document const& doc);
	
	void MapJson::ParseDOM(rapidjson::Value const& val, MapJson &to)
	{
		CPPUNIT_ASSERT(val.IsObject());
		
		//TODO//beacons
		auto &beacons_json = val["beacons"];
		for (rapidjson::SizeType i=0; i < beacons_json.Size(); i++) // Uses SizeType instead of size_t
			to.beacons.push_back(BeaconOnMapJson::ParseDOM(beacons_json[i]));
		to.description = val["description"].GetString();
		to.width = val["width"].Get<double>();
		to.height = val["height"].Get<double>();
		to.pixelSize = val["pixelSize"].Get<double>();
		to.path = val["path"].GetString();
		to.maskPath = val["maskPath"].GetString();
		to.mapUid = val["mapUid"].GetString();
		to.name = val["name"].GetString();
	}
	
	MapJson MapJson::ParseDOM(rapidjson::Value const& val)
	{
		MapJson to;
		ParseDOM(val,to);
		return to;
	}


	shared_ptr<MapJson> ReadOfficeMap()
	{
		constexpr auto office_map_file = "beacons-data-files/premises-info/office-map.json";
		FILE* fp = fopen(office_map_file, "rb"); // non-Windows use "r"
		char *readBuffer = new char[65536];  // max file size.
		//std::shared_ptr<char> sp( new char[size_of_input_file], std::default_delete<char[]>() );
		FileReadStream is(fp, readBuffer, 65536);
		Document doc;
		doc.ParseStream(is);
		//cout << endl << doc.IsNull() << "__" << endl;
		
		auto map = std::make_shared<MapJson>();
		MapJson::ParseDOM(doc[0], *map);
		
		fclose(fp);
		delete[] readBuffer;
		
		return map;
	}
	
	
	///\return List of received packets, ordered by time
	std::vector<BeaconReceivedDataJson> ReadSnifferedDataFromBeacons(char const *filepath)
	{
		FILE* fp = fopen(filepath, "rb");  // non-Windows use "r"
		char *readBuffer = new char[262144];  // max file size.
		//std::shared_ptr<char> sp( new char[size_of_input_file], std::default_delete<char[]>() );
		FileReadStream is(fp, readBuffer, 262144);
		Document doc;
		doc.ParseStream(is);
		
		// Check json-scheme and check file before parsing
		ItJim::BeaconReceivedDataJson::CheckDOM(doc);
		
		//auto beaconPackets = std::make_shared<BeaconReceivedDataJson>();
		std::vector<BeaconReceivedDataJson> beaconPackets;
		for( auto it = doc.Begin(); it != doc.End(); ++it ) {
			for (auto jt = it->Begin(); jt != it->End(); ++jt) {
				beaconPackets.push_back(
				       BeaconReceivedDataJson::ParseDOM(*jt)
				);
			}
		}
		std::sort(beaconPackets.begin(), beaconPackets.end());
		
		fclose(fp);
		delete[] readBuffer;
		return beaconPackets;
	}
	
	
	void BeaconDataFilesTest::test_20172402_063151()
	{
		using namespace Navigator;
		using namespace Navigator::Beacons;
		using namespace Navigator::Beacons::Factory;
		using Navigator::Math::Position3D;
		cout.precision(17);
		
		// Create the Beacon Navigator
		TrilatBeaconNavigator navigator(
				/*rssiFact*/make_shared<AlphaBetaFilterFactory>(0.85, 0.005),
				/*distFact*/make_shared<AlphaBetaFilterFactory>(0.85, 0.005)
		);
		
		// Read office map from .json to C++ struct
		auto map = ItJim::ReadOfficeMap();
		cout << "List beacons from map:" << endl;
		cout << "| macAddress | x | y | z | TxPower | damp |" << endl;
		for( auto b : map->beacons ){
			cout << b.macAddress << " \t" << b.x << " \t" << b.y << " \t" << b.z << " \t" << b.txpower << " \t" << b.damp << endl;
			// Add to Navigator
			navigator.addBeacon(
					Beacon(BeaconUID(b.macAddress), b.txpower, b.damp, Position3D(b.x, b.y, b.z) )
					);
		}
		
		auto receivedBeaconPackets = ItJim::ReadSnifferedDataFromBeacons("beacons-data-files/2017-24-02_06-31-51_bluetooth.json");
		cout << "List received data from beacons:" << endl;
		cout << "| MACaddress | RSSI | Timestamp | TxPower | distance |" << endl;
		for( auto b : receivedBeaconPackets ){
			cout << b.MACaddress << " \t" << b.RSSI << " \t" << b.TimeStamp << " \t" << b.TXpower << " \t" << b.distance << endl;
		}
		
		// Process every packet and write trace;
		cout << endl << "RESULT TRACE:" << endl;
		cout << "# \t | \t x \t | \t y \t | \t z \t |" << endl;
		int i=0;
		for( auto b : receivedBeaconPackets ){
			auto pos = navigator.process(
					BeaconReceivedData(b.TimeStamp, BeaconUID(b.MACaddress), b.RSSI)
			);
			cout << i++ << " \t |" << pos.x << "|\t" << pos.y << "|\t" << pos.z << endl;
		}
	}
	
	
} // namespace ItJim




/**
 * @brief Run all registered CppUnit tests
 * This version uses either standard (brief+compiler) or TeamCity output
 * @return   0    if success
 */
int main()
{
	using namespace CppUnit;
	
	// Force the teamcity-style output
	bool FORCE_TEAMCITY = false;
	// Do we use teamcity-style output ?
	bool useTeamcity = JetBrains::underTeamcity() || FORCE_TEAMCITY;
	
	// Create the event manager and test controller
	TestResult result;
	
	// Add either Brief or TeamCity progress listener
	BriefTestProgressListener briefProgress;
	JetBrains::TeamcityProgressListener teamProgress;
	
	if (useTeamcity) {
		result.addListener(&teamProgress);
	} else {
		result.addListener(&briefProgress);
	}
	
	// Add the collector as a listener
	// I don't use collector here much, but it can be useful for various outputs, like XML
	TestResultCollector collector;
	result.addListener(&collector);
	
	// The runner
	TestRunner runner;
	
	// Add all registered tests
	runner.addTest(TestFactoryRegistry::getRegistry().makeTest());
	
	// RUN all tests here
	runner.run(result);
	
	// Output the result with an outputter
	if (!useTeamcity) {
		CompilerOutputter outputter(&collector, cerr);
		outputter.write();
	}
	
	// Return number of failures or 0 if successful
	return collector.testFailures();
}
/*int main(int argc, char **argv)
{
	// Create the event manager and test controller
	TestResult controller;
	
	// Add a listener that collects test result
	TestResultCollector result;
	controller.addListener(&result);
	
	// Add the top suite to the test runner
	TestRunner runner;
	runner.addTest(TestFactoryRegistry::getRegistry().makeTest());
	
	// Listen to progress
	TestListener *listener;
	
	if (jetbrains::teamcity::underTeamcity()) {
		// Add unique flowId parameter if you want to run test processes in parallel
		// See http://confluence.jetbrains.net/display/TCD6/Build+Script+Interaction+with+TeamCity#BuildScriptInteractionwithTeamCity-MessageFlowId
		listener = new jetbrains::teamcity::TeamcityProgressListener();
	} else {
		listener = new BriefTestProgressListener();
	}
	controller.addListener(listener);
	
	// Run tests
	runner.run(controller);
	
	delete listener;
	
	return result.wasSuccessful() ? 0 : 1;
}*/
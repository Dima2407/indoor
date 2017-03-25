//
// Created by kyb on 15.03.17.
//


#include <iostream>
#include <cstdio>
#include <stdexcept>
//#include <experimental/filesystem>  // part of std:: since C++17

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "ItJim/JsonDataContract.h"
//#include "FilesystemHelper.h"

#include <cppunit/extensions/HelperMacros.h>
#include <sys/stat.h>


namespace ItJim {

	//using namespace CppUnit;
	using namespace std;
	namespace fs = boost::filesystem;
	
	using namespace Navigator;
	using namespace Navigator::Beacons;
	using namespace Navigator::Beacons::Factory;
	using Navigator::Math::Position3D;
	
	namespace JDC = JsonDataContract;
	
	
	class BeaconDataFilesTest : public CppUnit::TestCase
	{
		CPPUNIT_TEST_SUITE(BeaconDataFilesTest);
			
		CPPUNIT_TEST(beacon_data_files);
		//CPPUNIT_TEST(test_20172402_063151);
		//CPPUNIT_TEST(test_20172402_063308);
		//CPPUNIT_TEST(testNothing);
	
		CPPUNIT_TEST_SUITE_END();
	
	public:
		void test_20172402_063151();
		void test();
		void beacon_data_files();
		void test(const std::string &inPath);
		
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
	
	
	//void BeaconDataFilesTest::test_20172402_063151()
	//{
	//	using namespace Navigator;
	//	using namespace Navigator::Beacons;
	//	using namespace Navigator::Beacons::Factory;
	//	using Navigator::Math::Position3D;
	//	namespace fs = std::experimental::filesystem;
	//
	//	constexpr auto office_map_file = "beacons-data-files/premises-info/office-map.json";
	//	constexpr auto input_dir = "beacons-data-files/2017-24-02_06-31-51_bluetooth.json";
	//	constexpr auto input_file = "beacons-data-files/2017-24-02_06-31-51_bluetooth.json";
	//	constexpr auto output_dir = "calculated-trace";
	//	constexpr auto expected_trace_dir = "trace-20172402_063151.json";
	//	constexpr auto output_file = "trace-20172402_063151.json";
	//	//constexpr auto expected_trace_file_prefix = "trace-20172402_063151.json";
	//
	//	/*if(!DirectoryExists(output_dir))
	//		mkdir(output_dir);*/
	//	/*if( ! fs::exists( fs::path("calculated-trace") ) )
	//		fs::create_directory( fs::path("calculated-trace") );*/
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
	//	// Add beacons from map to navigator
	//	auto map = JsonDataContract::ReadOfficeMap(office_map_file);
	//	for (auto const& b : map->beacons) {
	//		navigator.addBeacon( b.toBeacon() );
	//	}
	//
	//	rapidjson::Document doc(rapidjson::kArrayType);
	//	FILE* fp = fopen(output_file, "w"); // non-Windows use "w", Windows "w"
	//	std::vector<char> json_buf(262144);
	//	rapidjson::FileWriteStream  os (fp, json_buf.data(), json_buf.capacity());
	//	rapidjson::PrettyWriter<rapidjson::FileWriteStream>  json_writer (os);
	//
	//	// Process every packet and write trace;
	//	cout << endl << "RESULT TRACE:" << endl;
	//	cout << "# \t | \t x \t | \t y \t |" << endl; //\t z \t |" << endl;
	//	cout.precision(2);
	//
	//	auto receivedBeaconPackets = JsonDataContract::ReadSnifferedDataFromBeacons(input_file);
	//	int i=0;
	//	for (auto const& b : receivedBeaconPackets) {
	//		JsonDataContract::OutputPosition pos = navigator.process(
	//				BeaconReceivedData(b.TimeStamp, BeaconUID(b.MACaddress), b.RSSI)
	//		);
	//		doc.PushBack( pos.toJson(doc), doc.GetAllocator());
	//		cout << i++ << " \t |" << pos.x << "|\t" << pos.y << "|\t" << pos.z << endl;
	//	}
	//
	//	doc.Accept(json_writer);
	//	fclose(fp);
	//}
	
	
	void WriteTraceToFile(vector<JDC::OutputPosition> const& trace, std::string const& filename = "trace.json")
	{
		FILE* fp = fopen(filename.c_str(), "w"); // non-Windows use "w", Windows "wb"
		assert(fp!=nullptr);
		std::vector<char> json_buf(262144);
		rapidjson::FileWriteStream  os (fp, json_buf.data(), json_buf.capacity());
		rapidjson::PrettyWriter<rapidjson::FileWriteStream>  json_writer (os);
		
		rapidjson::Document doc(rapidjson::kArrayType);
		for (auto const& pos : trace) {
			// Save position to JSON
			doc.PushBack( pos.toJson(doc), doc.GetAllocator() );
		}
		// Write to stream, stream writes to file
		doc.Accept(json_writer);
		fclose(fp);
	}
	
	
	void BeaconDataFilesTest::test()
	{
		using namespace Navigator;
		using namespace Navigator::Beacons;
		using namespace Navigator::Beacons::Factory;
		using Navigator::Math::Position3D;
		//namespace fs = std::experimental::filesystem;
		namespace rj = rapidjson;
		namespace JDC = JsonDataContract;
	
		constexpr auto office_map_file = "beacons-data-files/premises-info/office-map.json";
		constexpr auto input_dir = "beacons-data-files/";
		constexpr auto output_dir = "calculated-trace/";
		constexpr auto expected_trace_dir = "expected-trace/";
		constexpr auto output_file = "trace-20172402_063151.json";
		//constexpr auto expected_trace_file_prefix = "trace-20172402_063151.json";
	
		/*if(!DirectoryExists(output_dir))
			mkdir(output_dir);*/
		/*if( ! fs::exists( fs::path("calculated-trace") ) )
			fs::create_directory( fs::path("calculated-trace") );*/
	
		cout.precision(17);
	
		// Create the Beacon Navigator
		TrilatBeaconNavigator navigator(
				/*rssiFact*/make_shared<AlphaBetaFilterFactory>(0.85, 0.005),
				/*distFact*/make_shared<AlphaBetaFilterFactory>(0.85, 0.005)
		);
	
		// Read office map from .json to C++ struct
		// Add beacons from map to navigator
		auto map = JDC::ReadOfficeMap(office_map_file);
		for (auto const& b : map->beacons) {
			navigator.addBeacon( b.toBeacon() );
		}
		
		rapidjson::Document doc(rapidjson::kArrayType);
		vector<JDC::OutputPosition> trace;
		
		// Process every packet and write trace;
		cout << endl << "RESULT TRACE:" << endl;
		cout << "# \t | \t x \t | \t y \t |" << endl; //\t z \t |" << endl;
		cout.precision(2);
		
		auto receivedBeaconPackets = JDC::ReadSnifferedDataFromBeacons(""/*input_file*/);
		int i=0;
		for (auto const& b : receivedBeaconPackets) {
			// Calculate posistion
			JDC::OutputPosition pos = navigator.process(
					BeaconReceivedData(b.TimeStamp, BeaconUID(b.MACaddress), b.RSSI)
			);
			// Save position to JSON
			doc.PushBack( pos.toJson(doc), doc.GetAllocator() );
			cout << i++ << " \t |" << pos.x << "|\t" << pos.y << "|\t" << pos.z << endl;
		}
		
		FILE* fp = fopen(output_file, "w"); // non-Windows use "w", Windows "wb"
		std::vector<char> json_buf(262144);
		rapidjson::FileWriteStream  os (fp, json_buf.data(), json_buf.capacity());
		rapidjson::PrettyWriter<rapidjson::FileWriteStream>  json_writer (os);
		doc.Accept(json_writer);
		fclose(fp);
	}
	
	
	// Read map from .json to C++ struct
	// Add beacons from map to \par navigator
	void setMap(TrilatBeaconNavigator & navigator, std::string const& mapFile)
	{
		auto map = JsonDataContract::ReadOfficeMap(mapFile.c_str());
		for( auto const &b : map->beacons ){
			navigator.addBeacon( b.toBeacon() );
		}
	}
	
	
	/// Generate trace from input data
	///\param inPath to folder with data
	void BeaconDataFilesTest::test(const std::string &inPath)
	{
		constexpr auto _MapFileName_ = "map.json";
		constexpr auto _CollectedPacketsDir_ = "packets/";
		constexpr auto _StoreToDir_ = "trace/";
		
		// Create the Beacon Navigator
		TrilatBeaconNavigator navigator(
				/*rssiFact*/make_shared<AlphaBetaFilterFactory>(0.85, 0.005),
				/*distFact*/make_shared<AlphaBetaFilterFactory>(0.85, 0.005)
		);
		
		fs::path dirPath(inPath);
		assert(fs::is_directory(dirPath));
		
		// Add beacons to navigator from map.json
		fs::path mapPath(dirPath); mapPath.append(_MapFileName_);
		setMap(navigator, mapPath.string());
		
		cout << endl;
		const boost::regex my_filter( ".*\\.json" );
		dirPath.append(_CollectedPacketsDir_);
		if( fs::is_directory(dirPath) )
		{
			fs::directory_iterator end_itr;  // Default ctor yields past-the-end
			for( fs::directory_iterator itr( dirPath ); itr != end_itr; ++itr )
			{
				// Skip if not a file
				if( ! fs::is_regular_file( itr->status() ) )  continue;
				// Skip if no match
				if( ! boost::regex_match( itr->path().string(), my_filter ) )  continue;
				// File matches, print its name
				cout << "Read file " << itr->path().string() << endl;
				//
				auto receivedBeaconPackets = JDC::ReadSnifferedDataFromBeacons(itr->path().c_str());
				// Clear navigator history
				navigator.reset();
				// Begin calculating trace
				vector<JDC::OutputPosition> trace;
				for (auto const& b : receivedBeaconPackets){
					// Calculate posistion
					JDC::OutputPosition pos = navigator.process(
							BeaconReceivedData(b.TimeStamp, BeaconUID(b.MACaddress), b.RSSI)
					);
					trace.push_back(pos);
				}
				
				fs::path traceDir = _StoreToDir_;
				if( ! fs::is_directory(traceDir) )
					fs::create_directory(traceDir);
				std::string traceFilename = "trace-";
				traceFilename += itr->path().filename().string();
				WriteTraceToFile(trace, traceDir.append(traceFilename.c_str()).string() );
			}
		}
		
	}
	
	
	void BeaconDataFilesTest::beacon_data_files()
	{
		//test("beacons-data-files/");
		test("input/");
	}
		
} // namespace ItJim



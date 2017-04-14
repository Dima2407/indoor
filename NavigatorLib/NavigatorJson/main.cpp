//
// Created by kyb on 26.03.17.
//


#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "ItJim/JsonDataContract.h"


namespace ItJim {

	//using namespace CppUnit;
	using namespace std;
	namespace fs = boost::filesystem;
	
	using namespace Navigator;
	using namespace Navigator::Beacons;
	using namespace Navigator::Beacons::Factory;
	using Navigator::Math::Position3D;
	
	namespace JDC = JsonDataContract;
	namespace rj = rapidjson;

	namespace {
		using namespace ::rapidjson;
		using PrettyWriterWithNanAndInf = 
				rj::PrettyWriter<
						/*typename OutputStream  */ rj::FileWriteStream,
						/*typename SourceEncoding*/ UTF8<>,
						/*typename TargetEncoding*/ UTF8<>,
						/*typename StackAllocator*/ CrtAllocator
						,/*unsigned writeFlags*/    0 //(unsigned)kWriteNanAndInfFlag
				>;
	}
	
	void WriteTraceToFile(vector<JDC::OutputPosition> const& trace, std::string const& filename = "trace.json")
	{
		FILE* fp = fopen(filename.c_str(), "w"); // non-Windows use "w", Windows "wb"
		assert(fp!=nullptr);
		std::vector<char> json_buf(262144);
		rj::FileWriteStream  os (fp, json_buf.data(), json_buf.capacity());
		PrettyWriterWithNanAndInf  json_writer (os);
		
		rj::Document doc(rapidjson::kArrayType);
		for (auto const& pos : trace) {
			// Save position to JSON
			doc.PushBack( pos.toJson(doc), doc.GetAllocator() );
		}
		// Write to stream, stream writes to file
		bool done = doc.Accept(json_writer);
		if(!done)
			throw std::runtime_error("Failed to write rapidjson document to file stream");
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
	void test(const std::string &inPath)
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
				auto receivedBeaconPackets = JDC::ReadSnifferedDataFromBeacons(itr->path().string().c_str());
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
				cout << "Write file " << traceFilename << endl;
				WriteTraceToFile(trace, traceDir.append(traceFilename.c_str()).string() );
			}
		}
		
	}
	
		
} // namespace ItJim



int main(int argc, const char *argv[])
{
	ItJim::test("input/");
}

//
// Created by kyb on 20.03.17.
//

#include <iostream>
//#include <memory>
#include <algorithm>

#include "JsonDataContract.h"
//#include <cppunit/extensions/HelperMacros.h>

using namespace std;
using namespace rapidjson;


namespace ItJim {
	namespace JsonDataContract {
		
		
		/*void BeaconReceivedDataJson::CheckDOM(rapidjson::Document const& doc)
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
		}*/
		
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
		
		
		///\param doc Document - 2d array of BeaconReceivedDataJson
		///\return List of received packets, ordered by time
		BeaconReceivedDataJsonFile::
		BeaconReceivedDataJsonFile(rapidjson::Document const &doc)
		{
			// maybe todo Check json-scheme and check file before parsing
			//BeaconReceivedDataJson::CheckDOM(doc);
			for( auto it = doc.Begin(); it != doc.End(); ++it ) {
				for (auto jt = it->Begin(); jt != it->End(); ++jt) {
					this->push_back(
							BeaconReceivedDataJson::ParseDOM(*jt)
					);
				}
			}
			std::sort(this->begin(), this->end());
		}
		
		
		///\return List of received packets, ordered by time
		BeaconReceivedDataJsonFile ReadSnifferedDataFromBeacons(char const *filepath)
		{
			using namespace rapidjson;
			FILE* fp = fopen(filepath, "rb");  // non-Windows use "r"
			std::vector<char> buf(262144);
			FileReadStream is(fp, buf.data(), buf.capacity());
			Document doc;
			doc.ParseStream(is);  // after this buffer may/could be reused or deleted.
			fclose(fp);
			return BeaconReceivedDataJsonFile(doc);
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
			//TODO//beacons
			auto const &beacons_json = val["beacons"];
			//for (rapidjson::SizeType i=0; i < beacons_json.Size(); i++) // Uses SizeType instead of size_t
			//	to.beacons.push_back(BeaconOnMapJson::ParseDOM(beacons_json[i]));
			for( auto iter = beacons_json.Begin(); iter != beacons_json.End(); ++iter )
				to.beacons.push_back(BeaconOnMapJson::ParseDOM(*iter));
			//to.beacons.insert(to.beacons.end(), beacons_json.Begin(), beacons_json.End());
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
		
		
		void
		OutputPosition::
		ParseDOM(rapidjson::Value const& val, OutputPosition &to)
		{
			to.x = val["x"].Get<double>();
			to.y = val["y"].Get<double>();
			to.z = val["z"].Get<double>();
		}
		
		rapidjson::Value
		OutputPosition::
		toJson(rapidjson::Document & doc) const
		{
			namespace rj = rapidjson;
			auto ret = rapidjson::Value(kObjectType);
			if( isfinite(x) )  ret.AddMember( "x", this->x, doc.GetAllocator() );
			else               ret.AddMember( "x", StringRef( /*to_string(this->x).c_str()*/"nan" ), doc.GetAllocator() );
			if( isfinite(y) )  ret.AddMember( "y", this->y, doc.GetAllocator() );
			else               ret.AddMember( "y", StringRef( /*to_string(this->y).c_str()*/"nan" ), doc.GetAllocator() );
			if( isfinite(z) )  ret.AddMember( "z", this->z, doc.GetAllocator() );
			else               ret.AddMember( "z", StringRef( /*to_string(this->z).c_str()*/"nan" ), doc.GetAllocator() );
			return ret;
		}
		
		
		///
		/// \param value
		/// \return
		/*static*/
		std::vector<OutputPosition>
		OutputPosition::FromRapidJsonArrayToVector( rapidjson::Value const& value )
		{
			assert(value.IsArray());
			std::vector<OutputPosition> trace;
			for( auto it = value.Begin(); it != value.End(); ++it ) {
				trace.push_back(
						OutputPosition::ParseDOM(*it)
				);
			}
			return trace;
		}
		
		
		shared_ptr<MapJson> ReadOfficeMap(char const *filepath)
		{
			FILE* fp = fopen(filepath, "rb"); // non-Windows use "r"
			char *readBuffer = new char[65536];  // max file size.
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
		
		shared_ptr<MapJson> ReadOfficeMap(std::string const& filepath)
		{
			return ReadOfficeMap(filepath.c_str());
		}
		
		
		///
		std::vector<OutputPosition> ReadOutputPositionsFromRapidJsonArray(rapidjson::Value const &value)
		{
			assert(value.IsArray());
			std::vector<OutputPosition> trace;
			for( auto it = value.Begin(); it != value.End(); ++it ) {
				trace.push_back(
						OutputPosition::ParseDOM(*it)
				);
			}
			return trace;
		}
		
		
		///
		std::vector<OutputPosition> ReadOutputPositionsFromJsonFile(char const *filepath)
		{
			FILE* fp = fopen(filepath, "rb");  // non-Windows use "r"
			std::vector<char> buf(262144);
			FileReadStream is(fp, buf.data(), buf.capacity());
			Document doc;
			doc.ParseStream(is);  // after this buffer may/could be reused or deleted.
			fclose(fp);
			return ReadOutputPositionsFromRapidJsonArray(doc);
		}
		
		
	}  //namespace JsonDataContract
}  // namespace ItJim
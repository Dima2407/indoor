//
// Created by kyb on 20.03.17.
//

#include <iostream>
//#include <memory>
#include <algorithm>

#include "JsonDataContract.h"
#include <cppunit/extensions/HelperMacros.h>

using namespace std;


namespace ItJim {
	namespace JsonDataContract {
		
		
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
			auto ret = rapidjson::Value(kObjectType);
			ret.AddMember( "x", this->x, doc.GetAllocator() )
				.AddMember( "y", this->y, doc.GetAllocator() )
				.AddMember( "z", this->z, doc.GetAllocator() );
			return ret;
		}
		
		
		shared_ptr<MapJson> ReadOfficeMap(char const *filepath)
		{
			FILE* fp = fopen(filepath, "rb"); // non-Windows use "r"
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
			std::vector<char> readBuffe(262144);
			FileReadStream is(fp, readBuffe.data(), readBuffe.capacity());
			Document doc;
			doc.ParseStream(is);  // after this buffer may/could be reused or deleted.
			
			// Check json-scheme and check file before parsing
			BeaconReceivedDataJson::CheckDOM(doc);
			
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
			return beaconPackets;
		}
		
	}  //namespace JsonDataContract
}  // namespace ItJim
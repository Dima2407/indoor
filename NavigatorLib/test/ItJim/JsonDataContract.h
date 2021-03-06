//
// Created by kyb on 20.03.17.
//

#pragma once


#include <memory>

#include "rapidjson/rapidjson.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/error/en.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "Navigator.h"


namespace ItJim {
	namespace JsonDataContract {
		
		namespace rj = rapidjson;
		
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
		
		
		/// Файл с именем типа `2017-24-02_06-31-51_bluetooth.json`
		/// представляет собой 2ух мерный массив BeaconReceivedDataJson.
		/// 1 измерение массива - группировка по МАС, 2ое список пакетов пришедших от этого МАС
		//todo логичнее и правильнее хранить плоский одномерный массив упорядоченный по времени прихода пакетов,
		//todo так же как оно приходит в реальном устройстве
		struct BeaconReceivedDataJsonFile : std::vector<BeaconReceivedDataJson>
		{
		public:  // == CONSTRUCTORS ==
			BeaconReceivedDataJsonFile(rapidjson::Document const& doc);
		public:
			//static BeaconReceivedDataJsonFile ParseDOM(rapidjson::Document const& doc);
			//static void ParseDOM(rapidjson::Value const& val, BeaconReceivedDataJson &to);
			//static BeaconReceivedDataJson ParseDOM(rapidjson::Value const& val);
		};
		
		
		struct BeaconOnMapJson
		{
			double x;
			double y;
			double z;
			std::string macAddress;
			int    major;
			int    minor;
			double damp;
			double txpower;
		
		public:
			static void CheckDOM(rapidjson::Document const& doc);
			static void ParseDOM(rapidjson::Value const& val, BeaconOnMapJson &to);
			static BeaconOnMapJson ParseDOM(rapidjson::Value const& val);
		
		public:
			Navigator::Beacons::Beacon toBeacon() const {
				using namespace Navigator::Beacons;
				using namespace Navigator::Math;
				return Beacon(
						BeaconUID(this->macAddress),
						this->txpower,
						this->damp,
						Position3D(this->x, this->y, this->z));
			}
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
		
		
		struct OutputPosition : virtual public Navigator::Math::Position3D
		{
		public:  // === CONSTRUCTORS ===
			// Inherited constructor
			using Navigator::Math::Position3D::Position3D;
			OutputPosition(Navigator::Math::Position3D p3d){
				//*this = p3d;  // -> SIGSEGV
				this->x = p3d.x;
				this->y = p3d.y;
				this->z = p3d.z;
				//OutputPosition::Position3D(p3d);
			}
			OutputPosition() = default;
		public:  // === STATIC ===
			//static void CheckDOM(rapidjson::Document const& doc);
			static void ParseDOM(rapidjson::Value const& val, OutputPosition &to);
			static OutputPosition ParseDOM(rapidjson::Value const& val){
				OutputPosition to;
				OutputPosition::ParseDOM(val,to);
				return to;
			};
			static std::vector<OutputPosition> FromRapidJsonArrayToVector(rapidjson::Value const &value);
		public:
			///\note \param doc is needed to GetAllocator()
			rapidjson::Value toJson(rapidjson::Document &doc) const;
		};
		
		
		std::shared_ptr<MapJson> ReadOfficeMap(char const *filepath);
		BeaconReceivedDataJsonFile ReadSnifferedDataFromBeacons(char const *filepath);
	}
}

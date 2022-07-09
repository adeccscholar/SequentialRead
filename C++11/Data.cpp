#include "Data.h"

#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <functional>

std::ostream& operator << (std::ostream& out, TGeoLocation const& data) {
	out << std::setprecision(9) << data.Latitude() << "," << std::setprecision(9) << data.Longitude();
	return out;
   }

void swap(TGeoLocation& lhs, TGeoLocation& rhs) noexcept {
	std::swap(lhs.flLatitude, rhs.flLatitude);
	std::swap(lhs.flLongitude, rhs.flLongitude);
}

TGeoLocation::TGeoLocation(void) {
	_Init();
   }

TGeoLocation::TGeoLocation(TGeoLocation const& ref) {
	_Copy(ref);
   }

TGeoLocation::TGeoLocation(TGeoLocation&& ref) noexcept {
	swap(*this, ref);
   }

TGeoLocation::TGeoLocation(double const& pLatitude, double const& pLongitude) {
	flLatitude  = pLatitude;
	flLongitude = pLongitude;
   }

TGeoLocation& TGeoLocation::operator = (TGeoLocation const& ref) {
	Copy(ref);
	return *this;
   }

TGeoLocation& TGeoLocation::operator = (TGeoLocation && ref) noexcept {
	swap(*this, ref);
	return *this;
}

void TGeoLocation::Init(void) {
	_Init();
   }

void TGeoLocation::Copy(TGeoLocation const& ref) {
	_Copy(ref);
   }

TGeoPosition TGeoLocation::Calculate(TGeoLocation const& from) const {
	TGeoPosition ret;

	static const double r = 6371000.785;        ///< mean radius of the earth
	static const double pi = std::acos(-1);     // 3.14159265359  since C++20 use std::numbers::pi
	static const double w1 = pi / 180.0;
	static const double w2 = 180.0 / pi;
	double phiA = Latitude() * w1; /// 180.0 * M_PI;
	double lambdaA = Longitude() * w1; /// 180.0 * M_PI;
	double phiB = from.Latitude() * w1; /// 180.0 * M_PI;
	double lambdaB = from.Longitude() * w1; /// 180.0 * M_PI;
	double zeta = std::acos(std::sin(phiA) * std::sin(phiB) + std::cos(phiA) * std::cos(phiB) * std::cos(lambdaB - lambdaA));
	double tmp = (std::sin(phiB) - std::sin(phiA) * std::cos(zeta)) / (std::cos(phiA) * std::sin(zeta));
	double alpha = tmp < -1 ? 180.0 : tmp > 1 ? 0 : std::acos(tmp) * w2;
	ret.Distance(zeta * r);
	ret.Angle(lambdaA > lambdaB ? phiA > 0 ? 360.0 - alpha : 180.0 + alpha : phiA > 0 ? alpha : 180.0 - alpha);
	return ret;
   }

void TGeoLocation::_Init(void) {
	flLatitude  = 0.0;
	flLongitude = 0.0;
   }

void TGeoLocation::_Copy(TGeoLocation const& ref) {
	flLatitude  = ref.flLatitude;
	flLongitude = ref.flLongitude;
   }

int TGeoLocation::_Compare(TGeoLocation const& ref) const {
	int cmpLatitude = compare_val(flLatitude, ref.flLatitude);
	if (cmpLatitude == 0) return compare_val(flLongitude, ref.flLongitude);
	else return cmpLatitude;
   }

//==================================================================================

std::ostream& operator << (std::ostream& out, TGeoPosition const& data) {
	out << std::setprecision(3) << data.flDistance << " m, " << std::setprecision(3) << data.flAngle << " °";
	return out;
   }

void swap(TGeoPosition& lhs, TGeoPosition& rhs) noexcept {
	std::swap(lhs.flDistance, rhs.flDistance);
	std::swap(lhs.flAngle, rhs.flAngle);
   }

TGeoPosition::TGeoPosition(void) {
	_Init();
   }

TGeoPosition::TGeoPosition(TGeoPosition const& ref) {
	_Copy(ref);
   }

TGeoPosition::TGeoPosition(TGeoPosition&& ref) noexcept {
	swap(*this, ref);
}

TGeoPosition::TGeoPosition(double const& pDistance, double const& pAngle) {
	flDistance = pDistance;
	flAngle    = pAngle;
   }

TGeoPosition& TGeoPosition::operator = (TGeoPosition const& ref) {
	Copy(ref);
	return *this;
   }

TGeoPosition& TGeoPosition::operator = (TGeoPosition && ref) noexcept {
	swap(*this, ref);
	return *this;
   }

void TGeoPosition::Init(void) {
	_Init();
   }
	
void TGeoPosition::Copy(TGeoPosition const& ref) {
	_Copy(ref);
   }

void TGeoPosition::_Init(void) {
	flDistance = 0.0;
	flAngle    = 0.0;
   }

void TGeoPosition::_Copy(TGeoPosition const& ref) {
	flDistance = ref.flDistance;
	flAngle    = ref.flAngle;
   }

int TGeoPosition::_Compare(TGeoPosition const& ref) const {
	int cmpDistance = compare_val(flDistance, ref.flDistance);
	if (cmpDistance == 0) return compare_val(flAngle, ref.flAngle);
	return cmpDistance;
   }


//==================================================================================

std::ostream& operator << (std::ostream& out, TData const& data) {
	out << data.ZipCode() << " " << data.City() << " - " << data.District() << ", "
		 << data.Street() << " " << data.StreetNumber();
	return out;
   }

void swap(TData& lhs, TData& rhs) noexcept {
	swap(dynamic_cast<TGeoLocation&>(lhs), dynamic_cast<TGeoLocation&>(rhs));
	std::swap(lhs.strCity, rhs.strCity);
	std::swap(lhs.strStreet, rhs.strStreet);
	std::swap(lhs.strStreetNumber, rhs.strStreetNumber);
	std::swap(lhs.strZipCode, rhs.strZipCode);
	std::swap(lhs.strUrban_Unit, rhs.strUrban_Unit);
	std::swap(lhs.strOld_Unit, rhs.strOld_Unit);
	std::swap(lhs.strDistrict, rhs.strDistrict);
	swap(lhs.thePosition, rhs.thePosition);
   }

TData::TData(void) : TGeoLocation() {
	_Init();
   }

TData::TData(TData const& ref) : TGeoLocation(ref) {
	_Copy(ref);
   }

TData::TData(TData&& ref) noexcept {
	swap(*this, ref);
}


TData& TData::operator = (TData const& ref) {
	Copy(ref);
	return *this;
   }

TData& TData::operator = (TData && ref) noexcept {
	swap(*this, ref);
	return *this;
   }

TData& TData::operator = (TGeoPosition const& ref) {
	thePosition.Copy(ref);
	return *this;
   }


void TData::Init(void) {
	TGeoLocation::Init();
	_Init();
   }

void TData::Copy(TGeoLocation const& ref) {
	TGeoLocation::Copy(ref);
	try {
		TData const& detail = dynamic_cast<TData const&>(ref);
		_Copy(detail);
	   }
	catch (std::bad_cast&) {
		;
	   }
	}

void TData::_Init(void) {
	strCity         = "";
	strStreet       = "";
	strStreetNumber = "";
	strZipCode      = "";
	strUrban_Unit   = "";
	strOld_Unit     = "";
	strDistrict     = "";
	thePosition.Init();
   }

void TData::_Copy(TData const& ref) {
	strCity = ref.strCity;
	strStreet = ref.strStreet;
	strStreetNumber = ref.strStreetNumber;
	strZipCode = ref.strZipCode;
	strUrban_Unit = ref.strUrban_Unit;
	strOld_Unit = ref.strOld_Unit;
	strDistrict = ref.strDistrict;
	thePosition = ref.thePosition;
   }

int TData::_Compare(TData const& ref) const {
	int cmpCity = compare_val(City(), ref.City());
	if (cmpCity == 0) {
		int cmpUrban_Unit = compare_val(Urban_Unit(), ref.Urban_Unit());
		if (cmpUrban_Unit == 0) {
			int cmpDistrict = compare_val(District(), ref.District());
			if (cmpDistrict == 0) {
				int cmpStreet = compare_val(Street(), ref.Street());
				if (cmpStreet == 0) {
					return strStreetNumber < ref.StreetNumber() ? -1 : strStreetNumber > ref.StreetNumber() ? 1 : 0;
				   }
				else return cmpStreet;
			   }
			else return cmpDistrict;
		   }
		else return cmpUrban_Unit;
	   }
	else return cmpCity;
   }


//===================================================================================================

TProcesses::TProcesses(void) {
   }

TProcesses::TProcesses(TProcesses const& ref) {
	theAddresses = ref.theAddresses;
   }


void TProcesses::Read(std::string const& strFile) {
	static std::vector<std::function<void(TData&, std::string&&)>> funcs = {
			[](TData& data, std::string&& val) { data.City(std::forward<std::string>(val)); },
			[](TData& data, std::string&& val) { data.Street(std::forward<std::string>(val)); },
			[](TData& data, std::string&& val) { data.StreetNumber(std::forward<std::string>(val)); },
			[](TData& data, std::string&& val) { data.ZipCode(std::forward<std::string>(val)); },
			[](TData& data, std::string&& val) { data.Urban_Unit(std::forward<std::string>(val)); },
			[](TData& data, std::string&& val) { data.Old_Unit(std::forward<std::string>(val)); },
			[](TData& data, std::string&& val) { data.District(std::forward<std::string>(val)); },
			[](TData& data, std::string&& val) { data.Latitude(std::forward<std::string>(val)); },
			[](TData& data, std::string&& val) { data.Longitude(std::forward<std::string>(val)); }
	};

	std::ifstream ifs(strFile);
	if (ifs.is_open()) {
		TData data;
		std::string strRow;
		size_t iCount;
		while (std::getline(ifs, strRow)) {
			iCount = 0;
			size_t iPos = 0, iEnd;
			do {
				iEnd = strRow.find(";", iPos);
				funcs[iCount++](data, strRow.substr(iPos, iEnd - iPos));
				iPos = iEnd + 1;
			} while (iEnd != std::string::npos);
			theAddresses.emplace_back(std::move(data));
		   }
	   }
	else {
		std::ostringstream os;
		os << "error while opening file \"" << strFile << "\"" << std::endl;
		throw std::runtime_error(os.str().c_str());
	   }
	return;
   }

void TProcesses::Calculate(TGeoLocation const& geoloc) {
	for (auto& val : theAddresses) val = val.Calculate(geoloc);
   }

size_t TProcesses::Work(double const& flDist) {
	auto it = std::partition(theAddresses.begin(), theAddresses.end(), 
		        [&flDist](TData const& ref) -> bool { 
			        return ref.Position().Distance() < flDist;  
		           });
	return it - theAddresses.begin();
   }

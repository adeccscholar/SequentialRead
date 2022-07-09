#include "Data.h"

#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

std::ostream& operator << (std::ostream& out, TGeoLocation const& data) {
	out << std::setprecision(9) << data.Latitude() << "," << std::setprecision(9) << data.Longitude();
	return out;
   }

TGeoLocation::TGeoLocation(void) {
	_Init();
   }

TGeoLocation::TGeoLocation(TGeoLocation const& ref) {
	_Copy(ref);
   }

TGeoLocation::TGeoLocation(double const& pLatitude, double const& pLongitude) {
	flLatitude  = pLatitude;
	flLongitude = pLongitude;
   }

TGeoLocation& TGeoLocation::operator = (TGeoLocation const& ref) {
	Copy(ref);
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

TGeoPosition::TGeoPosition(void) {
	_Init();
   }

TGeoPosition::TGeoPosition(TGeoPosition const& ref) {
	_Copy(ref);
   }

TGeoPosition::TGeoPosition(double const& pDistance, double const& pAngle) {
	flDistance = pDistance;
	flAngle    = pAngle;
   }

TGeoPosition& TGeoPosition::operator = (TGeoPosition const& ref) {
	Copy(ref);
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

TData::TData(void) : TGeoLocation() {
	_Init();
   }

TData::TData(TData const& ref) : TGeoLocation(ref) {
	_Copy(ref);
   }

TData& TData::operator = (TData const& ref) {
	Copy(ref);
	return *this;
   }

TData& TData::operator += (TGeoPosition const& ref) {
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

std::string Read_helper(std::string const& strRow, size_t& iPos) {
	size_t iTmp = iPos, iEnd = strRow.find(";", iPos);
	iPos = iEnd + 1;
	return strRow.substr(iTmp, iEnd - iTmp);
   }

void TProcesses::Read(std::string const& strFile) {
	std::ifstream ifs(strFile.c_str());
	if (ifs.is_open()) {
		std::string strRow;
		TData theAddress;
		while (std::getline(ifs, strRow)) {
			int iCount = 0;
			size_t iPos = 0;
			theAddress.Init();
			theAddress.City(Read_helper(strRow, iPos));
			theAddress.Street(Read_helper(strRow, iPos));
			theAddress.StreetNumber(Read_helper(strRow, iPos));
			theAddress.ZipCode(Read_helper(strRow, iPos));
			theAddress.Urban_Unit(Read_helper(strRow, iPos));
			theAddress.Old_Unit(Read_helper(strRow, iPos));
			theAddress.District(Read_helper(strRow, iPos));
			double flValue = std::atof(Read_helper(strRow, iPos).c_str());
			theAddress.Latitude(flValue);
			flValue = std::atof(Read_helper(strRow, iPos).c_str());
			theAddress.Longitude(flValue);
			theAddresses.push_back(theAddress);
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
	for (itData it = theAddresses.begin(); it != theAddresses.end(); ++it) *it += it->Calculate(geoloc);
   }

class TDistHlp {
private:
	const double flComp;
public:
	TDistHlp(double const& val) : flComp(val) { }
	TDistHlp(TDistHlp const& ref) : flComp(ref.flComp) { }

	bool operator ()(TData const& ref) const { return ref.Position().Distance() < flComp; }
};

size_t TProcesses::Work(double const& flDist) {
	citData it = std::partition(theAddresses.begin(), theAddresses.end(), TDistHlp(flDist));
	return it - theAddresses.begin();
   }

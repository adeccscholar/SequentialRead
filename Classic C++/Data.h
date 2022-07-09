#pragma once
#include <iostream>
#include <string>
#include <vector>


class TGeoPosition {
	friend std::ostream& operator << (std::ostream& out, TGeoPosition const& data);
private:
	double      flDistance;
	double      flAngle;
public:
	TGeoPosition(void);
	TGeoPosition(TGeoPosition const&);
	TGeoPosition(double const&, double const&);
	virtual ~TGeoPosition(void) { }

	TGeoPosition& operator = (TGeoPosition const&);

	bool operator == (TGeoPosition const& ref) const { return _Compare(ref) == 0; }
	bool operator != (TGeoPosition const& ref) const { return _Compare(ref) != 0; }
	bool operator <  (TGeoPosition const& ref) const { return _Compare(ref) < 0; }
	bool operator <= (TGeoPosition const& ref) const { return _Compare(ref) <= 0; }
	bool operator >  (TGeoPosition const& ref) const { return _Compare(ref) > 0; }
	bool operator >= (TGeoPosition const& ref) const { return _Compare(ref) >= 0; }

	virtual void Init(void);
	virtual void Copy(TGeoPosition const&);

	double      const& Distance(void) const { return flDistance; }
	double      const& Angle(void) const { return flAngle; }

	double      const& Distance(double const& newVal) { return flDistance = newVal; }
	double      const& Angle(double const& newVal) { return flAngle = newVal; }

private:
	void _Init(void);
	void _Copy(TGeoPosition const&);
	int  _Compare(TGeoPosition const&) const;
};



class TGeoLocation {
	friend std::ostream& operator << (std::ostream& out, TGeoLocation const& data);
private:
	double      flLatitude;
	double      flLongitude;
public:
	TGeoLocation(void);
	TGeoLocation(TGeoLocation const&);
	TGeoLocation(double const&, double const&);

	virtual ~TGeoLocation(void) { }

	TGeoLocation& operator = (TGeoLocation const&);

	bool operator == (TGeoLocation const& ref) const { return _Compare(ref) == 0; }
	bool operator != (TGeoLocation const& ref) const { return _Compare(ref) != 0; }
	bool operator <  (TGeoLocation const& ref) const { return _Compare(ref) < 0; }
	bool operator <= (TGeoLocation const& ref) const { return _Compare(ref) <= 0; }
	bool operator >  (TGeoLocation const& ref) const { return _Compare(ref) > 0; }
	bool operator >= (TGeoLocation const& ref) const { return _Compare(ref) >= 0; }


	virtual void Init(void);
	virtual void Copy(TGeoLocation const&);

	double      const& Latitude(void) const { return flLatitude; }
	double      const& Longitude(void) const { return flLongitude; }

	double      const& Latitude(double& newVal) { return flLatitude = newVal; }
	double      const& Longitude(double& newVal) { return flLongitude = newVal; }

	TGeoPosition Calculate(TGeoLocation const&) const;

private:
	void _Init(void);
	void _Copy(TGeoLocation const&);
	int  _Compare(TGeoLocation const&) const;
   };



class TData : public TGeoLocation {
	friend std::ostream& operator << (std::ostream& out, TData const& data);

private:
	std::string  strCity;
	std::string  strStreet;
	std::string  strStreetNumber;
	std::string  strZipCode;
	std::string  strUrban_Unit;
	std::string  strOld_Unit;
	std::string  strDistrict;
	TGeoPosition thePosition;
public:
	TData(void);

	TData(TData const& ref);

	virtual ~TData(void) { }

	TData& operator = (TData const& ref);
	TData& operator += (TGeoPosition const& ref);

	operator TGeoPosition () const { return thePosition; }
	operator TGeoPosition const& () const { return thePosition; }


	virtual void Init(void);
	virtual void Copy(TGeoLocation const&);

	// Selectors
	std::string const& City(void) const { return strCity; }
	std::string const& Street(void) const { return strStreet; }
	std::string const& StreetNumber(void) const { return strStreetNumber; }
	std::string const& ZipCode(void) const { return strZipCode; }
	std::string const& Urban_Unit(void) const { return strUrban_Unit; }
	std::string const& Old_Unit(void) const { return strOld_Unit; }
	std::string const& District(void) const { return strDistrict; }

	TGeoPosition const& Position(void) const { return thePosition; }

	// Manipulators
	std::string const& City(std::string const& newVal) { return strCity = newVal; }
	std::string const& Street(std::string const& newVal) { return strStreet = newVal; }
	std::string const& StreetNumber(std::string const& newVal) { return strStreetNumber = newVal; }
	std::string const& ZipCode(std::string const& newVal) { return strZipCode = newVal; }
	std::string const& Urban_Unit(std::string const& newVal) { return strUrban_Unit = newVal; }
	std::string const& Old_Unit(std::string const& newVal) { return strOld_Unit = newVal; }
	std::string const& District(std::string const& newVal) { return strDistrict = newVal; }

	TGeoPosition&       Position(void)       { return thePosition; }

	bool operator == (TData const& ref) const { return _Compare(ref) == 0; }
	bool operator != (TData const& ref) const { return _Compare(ref) != 0; }
	bool operator <  (TData const& ref) const { return _Compare(ref) < 0; }
	bool operator <= (TData const& ref) const { return _Compare(ref) <= 0; }
	bool operator >  (TData const& ref) const { return _Compare(ref) > 0; }
	bool operator >= (TData const& ref) const { return _Compare(ref) >= 0; }

private:
	void _Init(void);
	void _Copy(TData const& ref);
	int  _Compare(TData const& ref) const;
};

typedef std::vector<TData>     myData;
typedef myData::iterator       itData;
typedef myData::const_iterator citData;


class TProcesses {
private:
	myData theAddresses;
public:
	TProcesses(void);
	TProcesses(TProcesses const&);
	virtual ~TProcesses(void) { };

	size_t CountOfAddresses(void) const { return theAddresses.size(); }
	void Read(std::string const& strFile);
	void Calculate(TGeoLocation const& geoloc);
	size_t Work(double const&);
};



template <typename ty>
inline int compare_val(ty const& left, ty const& right) {
	return left == right ? (left < right ? -1 : 1) : 0;
   }

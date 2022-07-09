#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <charconv>

class TGeoPosition {
	friend class TData;
	friend std::ostream& operator << (std::ostream& out, TGeoPosition const& data);

	friend void swap(TGeoPosition& lhs, TGeoPosition& rhs) noexcept;
private:
	double      flDistance;
	double      flAngle;
public:
	TGeoPosition(void);
	TGeoPosition(TGeoPosition const&);
	TGeoPosition(TGeoPosition&& ref) noexcept;
	TGeoPosition(double const&, double const&);
	virtual ~TGeoPosition(void) { }

	TGeoPosition& operator = (TGeoPosition const&);
	TGeoPosition& operator = (TGeoPosition &&) noexcept;

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

	void Distance(std::string&& newVal) { flDistance = std::stod(newVal); }
	void Angle(std::string&& newVal) { flAngle = std::stod(newVal); }


private:
	void _Init(void);
	void _Copy(TGeoPosition const&);
	int  _Compare(TGeoPosition const&) const;
};



class TGeoLocation {
	friend std::ostream& operator << (std::ostream& out, TGeoLocation const& data);
	friend void swap(TGeoLocation& lhs, TGeoLocation& rhs) noexcept;
private:
	double      flLatitude;
	double      flLongitude;
public:
	TGeoLocation(void);
	TGeoLocation(TGeoLocation const&);
	TGeoLocation(TGeoLocation&&) noexcept;
	TGeoLocation(double const&, double const&);

	virtual ~TGeoLocation(void) { }

	TGeoLocation& operator = (TGeoLocation const&);
	TGeoLocation& operator = (TGeoLocation &&) noexcept;

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

	void Latitude(std::string && newVal) { flLatitude = std::stod(newVal); }
   void Longitude(std::string && newVal) { flLongitude = std::stod(newVal); }

	void Latitude(std::string_view const& newVal) { auto result = std::from_chars(newVal.data(), newVal.data() + newVal.size(), flLatitude); }
	void Longitude(std::string_view const& newVal) { auto result = std::from_chars(newVal.data(), newVal.data() + newVal.size(), flLongitude); }


	TGeoPosition Calculate(TGeoLocation const&) const;

private:
	void _Init(void);
	void _Copy(TGeoLocation const&);
	int  _Compare(TGeoLocation const&) const;
   };



class TData : public TGeoLocation {
	friend std::ostream& operator << (std::ostream& out, TData const& data);
	friend void swap(TData& lhs, TData& rhs) noexcept;
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
	TData(TData&& ref) noexcept;

	virtual ~TData(void) { }

	TData& operator = (TData const& ref);
	TData& operator = (TData && ref) noexcept;
	TData& operator = (TGeoPosition const& ref);

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

	// rvalue manipulators
	void City(std::string&& newVal) { strCity = std::forward<std::string>(newVal); }
	void Street(std::string&& newVal) { strStreet = std::forward<std::string>(newVal); }
	void StreetNumber(std::string&& newVal) { strStreetNumber = std::forward<std::string>(newVal); }
	void ZipCode(std::string&& newVal) { strZipCode = std::forward<std::string>(newVal); }
	void Urban_Unit(std::string&& newVal) { strUrban_Unit = std::forward<std::string>(newVal); }
	void Old_Unit(std::string&& newVal) { strOld_Unit = std::forward<std::string>(newVal); }
	void District(std::string&& newVal) { strDistrict = std::forward<std::string>(newVal); }

	void Distance(std::string&& newVal) { thePosition.Distance(std::stod(newVal)); }
	void Angle(std::string&& newVal) { thePosition.Angle(std::stod(newVal)); }

	// string_view manipulators
	void City(std::string_view const& newVal) { strCity = move(std::string{ newVal.data(), newVal.size() }); }
	void Street(std::string_view const& newVal) { strStreet = move(std::string{ newVal.data(), newVal.size() }); }
	void StreetNumber(std::string_view const& newVal) { strStreetNumber = move(std::string{ newVal.data(), newVal.size() }); }
	void ZipCode(std::string_view const& newVal) { strZipCode = move(std::string{ newVal.data(), newVal.size() }); }
	void Urban_Unit(std::string_view const& newVal) { strUrban_Unit = move(std::string{ newVal.data(), newVal.size() }); }
	void Old_Unit(std::string_view const& newVal) { strOld_Unit = move(std::string{ newVal.data(), newVal.size() }); }
	void District(std::string_view const& newVal) { strDistrict = move(std::string{ newVal.data(), newVal.size() }); }

	void Distance(std::string_view const& newVal) { auto result = std::from_chars(newVal.data(), newVal.data() + newVal.size(), thePosition.flDistance); }
	void Angle(std::string_view const& newVal) { auto result = std::from_chars(newVal.data(), newVal.data() + newVal.size(), thePosition.flAngle); }


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

using myData  = std::vector<TData>;
using itData  = myData::iterator;
using citData = myData::const_iterator;


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

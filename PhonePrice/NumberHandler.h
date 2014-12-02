#pragma once

class CNumberHandler
{
public:
	CNumberHandler(void){}
	virtual ~CNumberHandler(void){}
	virtual void  NormanizeString(const CString& src,CString& to)=0;

};

class CScreenNumberHandler:public CNumberHandler{
public:
	void  NormanizeString(const CString& src,CString& to){
		to=src;
		if(src.Compare(L"6.4")>=0){
			to=L"6.4寸以上";
		}else if(src.Compare(L"6.1")>=0){
			to=L"6.1-6.3";
		}else if(src.Compare(L"5.6")>=0){
			to=L"5.6-5.8";
		}else if(src.Compare(L"5.4")>=0){
			to=L"5.4-5.5";
		}else if(src.Compare(L"5.1")>=0){
			to=L"5.1-5.3";
		}else if(src.Compare(L"4.9")>=0){
			to=L"4.9-5.0";
		}else if(src.Compare(L"4.6")>=0){
			to=L"4.6-4.8";
		}else if(src.Compare(L"4.3")>=0){
			to=L"4.3-4.5";
		}else if(src.Compare(L"4.0")>=0 || src[0]==L'4'){
			to=L"4.0";
		}else if(src.Compare(L"3.5寸以下")==0){
			to=L"3.5寸以下";
		}else if(src.Compare(L"3.5")>=0){
			to=L"3.5";
		}else{
			to=L"3.5寸以下";
		}
	}

};


class CPCameraNumberHandler:public CNumberHandler{
public:
	void  NormanizeString(const CString& src,CString& to){
		int len=src.GetLength();
		to=src;
		if(len<=2 || src==L"300以下"){
			to=L"300以下";
		}else if(len==3){
			if(src==L'800'){
				to=L'800';
			}else if(src.Compare(L"800")>=0){
				to=L"800-1200";		
			}else if(src.Compare(L"600")>=0){
				to=L"600-700";		
			}else if(src.Compare(L"500")>=0){
				to=L"500";
			}else if(src.Compare(L"400")>=0){
				to=L"400";
			}else{
				to=L"300以下";		
			}
		}else if(len==4){
			if(src.Compare(L"1200")<=0){
				to=L"800-1200";		
			}else if(src.Compare(L"1300")<=0){
				to=L"1300";		
			}else if(src.Compare(L"4100")>=0){
				to=L"4100";
			}else{
				to=L"1300";		
			}
		}
	}

};
class CSCameraNumberHandler:public CNumberHandler{
public:
	void  NormanizeString(const CString& src,CString& to){
		int len=src.GetLength();
		to=src;
		if(len<=2){
			if(src.Compare(L"50")>0){
				to=L"100-200";
			}else if(src.Compare(L"30")>=0){
				to=L"30";
			}else{
				to=L"不支持";
			}
		}else if(len==3){
			if(src==L"不支持"){
				to=L"不支持";
			}else if(src.Compare(L"800")>=0){
				to=L"800";		
			}else if(src.Compare(L"500")>=0){
				to=L"500";		
			}else if(src.Compare(L"400")>=0){
				to=L"400";		
			}else if(src.Compare(L"300")>=0){
				to=L"300";
			}else if(src.Compare(L"100")>=0){
				to=L"100-200";
			}else{
				to=L"100-200";	
			}
		}else{
			// to=L"800";
		}

	}

};
class CRamNumberHandler:public CNumberHandler{
public:
	void  NormanizeString(const CString& src,CString& to){
		int len=src.GetLength();
		to=src;
		if(len==4){
		if(src.Compare(L"3000")>=0){
			to=L"3000";
		}
			else if(src.Compare(L"2048")>=0){
				to=L"2048以上";
			}else if(src.Compare(L"1536")>=0){
				to=L"1536";
			}else if(src.Compare(L"1024")>=0){
				to=L"1024";
			}else{
				to=L"1024";
			}
		}else if(len==3){
			if(src.Compare(L"800")>=0){
				to=L"800";
			}else if(src.Compare(L"768")>=0){
				to=L"768";
			}else if(src.Compare(L"512")>=0){
				to=L"512";
			}else if(src.Compare(L"256")>=0){
				to=L"256";
			}else if(src.Compare(L"128")<0){
				to=L"128以下";
			}else{
				to=L"256";
			}
		}else if(len<=2){
			to=L"128以下";
		}
	}

};
class CRomNumberHandler:public CNumberHandler{
public:
	void  NormanizeString(const CString& src,CString& to){
		to=src;
		int len=src.GetLength();
		if(len>5){
			to=L"16";
		}else if(len==5){
			if(src.Compare(L"32000")>=0){
				to=L"32";
			}else{
				to=L"16";
			}
		}else if(len==4){
			if(src.Compare(L"8000")>=0){
				to=L"8";
			}else if(src.Compare(L"4000")>=0){
				to=L"4";
			}else if(src.Compare(L"2000")>=0){
				to=L"2";
			}else if(src.Compare(L"1000")>=0){
				to=L"1";
			}else{
				to=L"1";
			}
		}else if(len==3){
			if(src[0]==L'0' && src[1]==L'.'){
				to=L"2及以下";
			}
			if(src==L"16G"){
				to=L"16";
			}else if(src==L"32G"){
				to=L"32";
			}else{
				to=L"16";
			}
		}else if(len==2){
			if(src==L"8G"){
				to=L"8";
			}else if(src==L"4G"){
				to=L"4";
			}else if(src==L"2G"){
				to=L"2及以下";
			}
		}
	}

};
class CStandbyNumberHandler:public CNumberHandler{
public:
	void  NormanizeString(const CString& src,CString& to){
		to=src;
		if(src==L"单网单待"){
			to="单卡单待";
		}else if(src==L"双网单待"){
			to="双卡单待";
		}else if(src==L"双网双待"){
			to="双卡双待";
		}
	}

};
class CResolveNumberHandler:public CNumberHandler{
public:
	void  NormanizeString(const CString& src,CString& to){
		to=src;
	}

};
class CCoreNumNumberHandler:public CNumberHandler{
public:
	void  NormanizeString(const CString& src,CString& to){
		to=src;
		if(src==L"八核"){
			to=L"8";
		}else if(src==L"四核"){
			to=L"4";
		}else if(src==L"双核"){
			to=L"2";
		}else if(src==L"单核"){
			to=L"1";
		}
	}

};
class CCpuFreqNumberHandler:public CNumberHandler{
public:
	void  NormanizeString(const CString& src,CString& to){
		int len=src.GetLength();
		to=src;
		if(len==4){
			if(src.Compare(L"4096")>=0){
				to=L"4096";
			}else if(src.Compare(L"2048")>=0){
				to=L"2048";
			}else if(src.Compare(L"1741")>=0){
				to=L"1741";
			}else if(src.Compare(L"1400")>=0){
				to=L"1400-1638";
			}else{
				to=L"1228以下";
			}

		}else if(len<=3){
			to=L"1228以下";
		}
	}

};
class CBatteryNumberHandler:public CNumberHandler{
public:
	void  NormanizeString(const CString& src,CString& to){
		int len=src.GetLength();
		to=src;
		if(len==4){
			if(src.Compare(L"4000")>=0){
				to=L"4050";
			}else if(src.Compare(L"3500")>=0){
				to=L"3500";
			}else if(src.Compare(L"3200")>=0){
				to=L"3200";
			}else if(src.Compare(L"3150")>=0){
				to=L"3150";
			}else if(src.Compare(L"3000")>=0){
				to=L"3000";
			}else if(src.Compare(L"2900")>=0){
				to=L"2900";
			}else if(src.Compare(L"2500")>=0){
				to=L"2500";
			}else if(src.Compare(L"2000")>=0){
				to=L"2000-2200";
			}else if(src.Compare(L"1900")>=0){
				to=L"1900";
			}else if(src.Compare(L"1800")>=0){
				to=L"1800";
			}else if(src.Compare(L"1750")>=0){
				to=L"1750";
			}else if(src.Compare(L"1700")>=0){
				to=L"1700";
			}else if(src.Compare(L"1650")>=0){
				to=L"1650";
			}else if(src.Compare(L"1600")>=0){
				to=L"1600";
			}else if(src.Compare(L"1520")>=0){
				to=L"1520";
			}else if(src.Compare(L"1500")>=0){
				to=L"1500";
			}else{
				to=L"1450以下";
			}

		}else if(len<=3){
			to=L"1450以下";
		}
	}

};
// PhonePriceDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "string_util.h"
#include <map>

struct ValueItem{
	ValueItem():targetId(0),weight(0){};
	ValueItem(int t,double w):targetId(t),weight(w){};
	ValueItem(const ValueItem& rhs):targetId(rhs.targetId),weight(rhs.weight){};
	//对标号码，如果有的话
	int targetId;
	// 乘数
	double weight;
};
struct RelocateInfo{
	RelocateInfo():rank(0x7FFFFFFF),weight(0),price(0){}
	RelocateInfo(const RelocateInfo& rhs):phoneName(rhs.phoneName),rank(rhs.rank),weight(rhs.weight),price(rhs.price),supplyPrice(rhs.supplyPrice){}
	RelocateInfo& operator=(const RelocateInfo& rhs){
		this->phoneName.assign(rhs.phoneName);
		this->rank=rhs.rank;
		this->weight=rhs.weight;
		this->price=rhs.price;
		this->supplyPrice=rhs.supplyPrice;
		return *this;
	}
	UnicodeStr phoneName;
	int rank;
	double weight;
	int price;
	int supplyPrice;
};
struct Top3Relocation{
	Top3Relocation(){}
	Top3Relocation(const Top3Relocation& rhs):top1(rhs.top1),top2(rhs.top2),top3(rhs.top3){}
	RelocateInfo top1;
	RelocateInfo top2;
	RelocateInfo top3;
};

// CPhonePriceDlg 对话框
class CPhonePriceDlg : public CDialog
{
// 构造
public:
	CPhonePriceDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PHONEPRICE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeBrand();
	afx_msg void OnCbnSelchangeComboPmdx();
	afx_msg void OnCbnSelchangeZsxtCombo();
protected:
	CComboBox mBrandCombo;
	CComboBox mPmdxCombom;
	CComboBox mZsxtCombo;
	CComboBox mSksdCmobo;
	CComboBox mRamCombo;
	CComboBox mRomCombo;
	CComboBox mPmfblCombo;
	CComboBox mFsxtCombo;
	CComboBox mHxsCombo;
	CComboBox mCpuCombo;
	CComboBox mDcrlCombo;
	CComboBox mWllxCombo;
	void UpdatePrice();
public:
	afx_msg void OnCbnSelchangeDcrlCombo();
	afx_msg void OnCbnSelchangeWllxCombo();
public :
	int CalcPrice(const UnicodeStr& brand,
		const UnicodeStr& screen,
		const UnicodeStr& pcamera,
		const UnicodeStr& standby,
		const UnicodeStr& ram,
		const UnicodeStr& rom,
		const UnicodeStr& resolve,
		const UnicodeStr& scamera,
		const UnicodeStr& coreNum,
		const UnicodeStr& cpuFreq,
		const UnicodeStr& battery,
		const UnicodeStr& network,
		Top3Relocation* relocation);
	
	int CalcSupplyPrice(const UnicodeStr& brand,
		const UnicodeStr& screen,
		const UnicodeStr& pcamera,
		const UnicodeStr& standby,
		const UnicodeStr& ram,
		const UnicodeStr& rom,
		const UnicodeStr& resolve,
		const UnicodeStr& scamera,
		const UnicodeStr& coreNum,
		const UnicodeStr& cpuFreq,
		const UnicodeStr& battery,
		const UnicodeStr& network,
		Top3Relocation* relocation);

	CRichEditCtrl mDcjgRichEdit;
	CRichEditCtrl mZgjgRichEdit;
	std::map<UnicodeStr,ValueItem> mBrandTable;
	std::map<UnicodeStr,ValueItem> mScreenTable;
	std::map<UnicodeStr,ValueItem> mPCameraTable;

	std::map<UnicodeStr,double> mStandbyTable;
	std::map<UnicodeStr,double> mRamTable;
	std::map<UnicodeStr,double> mRomTable;
	std::map<UnicodeStr,double> mResolveTable;
	std::map<UnicodeStr,double> mSCameraTable;
	std::map<UnicodeStr,double> mCoreNumTable;
	std::map<UnicodeStr,double> mCpuTable;
	std::map<UnicodeStr,double> mBatteryTable;
	std::map<UnicodeStr,double> mNetworkTable;
	std::map<std::string,Top3Relocation> mRelocateTable;
	std::map<UnicodeStr,UnicodeStr> mBrandMapTable;

	ValueItem defBrandVItem;
	ValueItem defScreenVItem;
	ValueItem defPcameraVItem;

	double defStandbyW;
	double defRamW;
	double defRomW;
	double defResolveW;
	double defSCameraW;
	double defCoreNumW;
	double defCpuW;
	double defBatteryW;
	double defNetworkW;


	afx_msg void OnCbnSelchangeSksdCombo();
	afx_msg void OnCbnSelchangeRamCombo();
	afx_msg void OnCbnSelchangeRomCombo();
	afx_msg void OnCbnSelchangePmfblCombo();
	afx_msg void OnCbnSelchangeFsxtCombo();
	afx_msg void OnCbnSelchangeHxsCombo();
	afx_msg void OnCbnSelchangeCpuCombo();
	afx_msg void OnBnClickedButtonBtach();
	CStatic mDBTop1Text;
	CStatic mDBTop2Text;
	CStatic mDBTop3Text;
};

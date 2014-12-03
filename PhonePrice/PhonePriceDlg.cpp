// PhonePriceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <vector>
#include "PhonePrice.h"
#include "PhonePriceDlg.h"
#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "ini.h"
#include "NumberHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static void InitFirtRowComboBox(CComboBox& brandCombo,const std::map<UnicodeStr,ValueItem>& table){
	int i=0;
	for(std::map<UnicodeStr,ValueItem>::const_iterator cit=table.begin();cit!=table.end();cit++){
		brandCombo.InsertString(i,reinterpret_cast<LPCTSTR>(cit->first.c_str()));
		i+=1;
	}
	brandCombo.SetCurSel(0);
}
static void InitSecondRowComboBox(CComboBox& brandCombo,const std::map<UnicodeStr,double>& table){
	int i=0;
	for(std::map<UnicodeStr,double>::const_iterator cit=table.begin();cit!=table.end();cit++){
		brandCombo.InsertString(i,reinterpret_cast<LPCTSTR>(cit->first.c_str()));
		i+=1;
	}
	brandCombo.SetCurSel(0);
}
static int conf_handler(void* user, const char* section, const char* name, const char* value){
	CPhonePriceDlg* dlg = (CPhonePriceDlg*)user;
	char* ptr = NULL;
	std::vector<std::string> values;
	UnicodeStr ustr;
	ValueItem vi;
#define MATCH(s) strcmp(section, s) == 0
	if (MATCH("brand")) {
		StringUtil::SplitString(value,strlen(value),'\t',&values);
		StringUtil::u8tou16(name,strlen(name),ustr);
		vi.targetId=atoi(values[1].c_str());
		vi.weight=strtod(values[0].c_str(),&ptr);
		dlg->mBrandTable[ustr]=vi;
		if(vi.targetId>dlg->defBrandVItem.targetId){
			dlg->defBrandVItem.targetId=vi.targetId;
		}
		if(vi.weight<dlg->defBrandVItem.weight){
			dlg->defBrandVItem.weight=vi.weight;
		}
	}else if (MATCH("brandmap")) {
		UnicodeStr toStr;
		StringUtil::u8tou16(value,strlen(value),toStr);
		StringUtil::u8tou16(name,strlen(name),ustr);
		dlg->mBrandMapTable[ustr]=toStr;
	}else if (MATCH("screen")) {
		StringUtil::SplitString(value,strlen(value),'\t',&values);
		StringUtil::u8tou16(name,strlen(name),ustr);
		vi.targetId=atoi(values[1].c_str());
		vi.weight=strtod(values[0].c_str(),&ptr);
		dlg->mScreenTable[ustr]=vi;
		if(vi.targetId>dlg->defScreenVItem.targetId){
			dlg->defScreenVItem.targetId=vi.targetId;
		}
		if(vi.weight<dlg->defScreenVItem.weight){
			dlg->defScreenVItem.weight=vi.weight;
		}
	}else if (MATCH("pcamera")) {
		StringUtil::SplitString(value,strlen(value),'\t',&values);
		StringUtil::u8tou16(name,strlen(name),ustr);
		vi.targetId=atoi(values[1].c_str());
		vi.weight=strtod(values[0].c_str(),&ptr);
		dlg->mPCameraTable[ustr]=vi;
		if(vi.targetId>dlg->defPcameraVItem.targetId){
			dlg->defPcameraVItem.targetId=vi.targetId;
		}
		if(vi.weight<dlg->defPcameraVItem.weight){
			dlg->defPcameraVItem.weight=vi.weight;
		}
	} else if (MATCH("ram")) {
		StringUtil::u8tou16(name,strlen(name),ustr);
		double v=strtod(value,&ptr);
		dlg->mRamTable[ustr]=v;
		if(v<dlg->defRamW){
			dlg->defRamW=v;
		}
	}else if (MATCH("rom")) {
		StringUtil::u8tou16(name,strlen(name),ustr);
		double v=strtod(value,&ptr);
		dlg->mRomTable[ustr]=v;
		if(v<dlg->defRomW){
			dlg->defRomW=v;
		}
	}else if (MATCH("resolve")) {
		StringUtil::u8tou16(name,strlen(name),ustr);
		double v=strtod(value,&ptr);
		dlg->mResolveTable[ustr]=v;
		if(v<dlg->defResolveW){
			dlg->defResolveW=v;
		}
	}else if (MATCH("scamera")) {
		StringUtil::u8tou16(name,strlen(name),ustr);
		double v=strtod(value,&ptr);
		dlg->mSCameraTable[ustr]=v;
		if(v<dlg->defSCameraW){
			dlg->defSCameraW=v;
		}
	}else if (MATCH("corenum")) {
		StringUtil::u8tou16(name,strlen(name),ustr);
		double v=strtod(value,&ptr);
		dlg->mCoreNumTable[ustr]=v;
		if(v<dlg->defCoreNumW){
			dlg->defCoreNumW=v;
		}
	}else if (MATCH("battery")) {
		StringUtil::u8tou16(name,strlen(name),ustr);
		double v=strtod(value,&ptr);
		dlg->mBatteryTable[ustr]=v;
		if(v<dlg->defBatteryW){
			dlg->defBatteryW=v;
		}
    }else if (MATCH("network")) {
		StringUtil::u8tou16(name,strlen(name),ustr);
		double v=strtod(value,&ptr);
		dlg->mNetworkTable[ustr]=v;
		if(v<dlg->defNetworkW){
			dlg->defNetworkW=v;
		}
	}else if (MATCH("cpufreq")) {
		StringUtil::u8tou16(name,strlen(name),ustr);
		double v=strtod(value,&ptr);
		dlg->mCpuTable[ustr]=v;
		if(v<dlg->defCpuW){
			dlg->defCpuW=v;
		}
	}else if (MATCH("standby")) {
		StringUtil::u8tou16(name,strlen(name),ustr);
		double v=strtod(value,&ptr);
		dlg->mStandbyTable[ustr]=v;
		if(v<dlg->defStandbyW){
			dlg->defStandbyW=v;
		}
	}else if (MATCH("relocate")) {
		StringUtil::SplitString(value,strlen(value),'\t',&values);
		RelocateInfo info;
		info.rank=atoi(values[0].c_str()+3);
		info.weight=strtod(values[1].c_str(),&ptr);
		info.price=atoi(values[2].c_str());
		info.supplyPrice=atoi(values[3].c_str());
		std::string relocateKey(name,strlen(name));
		StringUtil::u8tou16(values[4].c_str(),values[4].size(),info.phoneName);
		std::map<std::string,Top3Relocation>::iterator it=dlg->mRelocateTable.find(relocateKey);
		if(it==dlg->mRelocateTable.end()){
			Top3Relocation rel;
			rel.top1=info;
			dlg->mRelocateTable[relocateKey]=rel;
		}else{
			Top3Relocation& rel=it->second;
			if(info.rank <rel.top1.rank){
				rel.top3=rel.top2;
				rel.top2=rel.top1;
				rel.top1=info;
			}else if(info.rank <rel.top2.rank && info.rank!=rel.top1.rank){
				rel.top3=rel.top2;
				rel.top2=info;
			}else if(info.rank < rel.top3.rank && info.rank!=rel.top2.rank){
				rel.top3=info;
			}
		}
	}else {
		MessageBoxA(NULL,section,NULL,MB_OK);
		return 0; /* unknown section/name, error */
	}
#undef MATCH
return 1;
}
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPhonePriceDlg 对话框
double lookupValue(const std::map<UnicodeStr,double>& table,const UnicodeStr& ustr,double def){
	std::map<UnicodeStr,double>::const_iterator cit=table.find(ustr);
	if(cit==table.end()){
		return def;
	}
	return cit->second;
}

int CPhonePriceDlg::CalcPrice(const UnicodeStr& brand,
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
			  Top3Relocation* relocation){
	char buffer[16]={0};
	ValueItem viBrand=defBrandVItem;
	std::map<UnicodeStr,ValueItem>::const_iterator cit=mBrandTable.find(brand);
	if(cit!=mBrandTable.end()){
		viBrand=cit->second;
	}else{
		// MessageBoxW((LPCTSTR)brand.c_str(),L"No brand");
	}
	ValueItem viScreen=defScreenVItem;
	cit=mScreenTable.find(screen);
	if(cit!=mScreenTable.end()){
		viScreen=cit->second;
	}else{
		// MessageBoxW((LPCTSTR)screen.c_str(),L"No Screen");
	}
	ValueItem viPCamera=defPcameraVItem;
	cit=mPCameraTable.find(pcamera);
	// MessageBox(LPCTSTR(pcamera.c_str()));
	if(cit!=mPCameraTable.end()){
		viPCamera=cit->second;
	}else{
		//MessageBoxW((LPCTSTR)pcamera.c_str(),L"No PCamera");
	}
	double standbyW=lookupValue(mStandbyTable,standby,defStandbyW);
	double ramW=lookupValue(mRamTable,ram,defRamW);
	double romW=lookupValue(mRomTable,rom,defRomW);
	double resolveW=lookupValue(mResolveTable,resolve,defResolveW);
	double scameraW=lookupValue(mSCameraTable,scamera,defSCameraW);
	double coreNumW=lookupValue(mCoreNumTable,coreNum,defCoreNumW);
	double cpuFreqW=lookupValue(mCpuTable,cpuFreq,defCpuW);
	double batteryW=lookupValue(mBatteryTable,battery,defBatteryW);
	double networkW=lookupValue(mNetworkTable,network,defNetworkW);
    double totalProductW=viBrand.weight*viScreen.weight*viPCamera.weight;
	totalProductW=totalProductW*standbyW*ramW*romW*resolveW*scameraW*coreNumW*cpuFreqW*batteryW*networkW;
	int len=sprintf(buffer,"%d%d%d",viBrand.targetId,viScreen.targetId,viPCamera.targetId);
	std::string reTarget(buffer,len);
	
	std::map<std::string,Top3Relocation>::const_iterator ncit=mRelocateTable.find(reTarget);
	if(ncit==mRelocateTable.end()){
		// MessageBoxA(NULL,reTarget.c_str(),"No result",MB_OK);
		return 0;
	}
	// MessageBoxA(NULL,reTarget.c_str(),"got result",MB_OK);
	if(relocation){
		*relocation=ncit->second;
	}
	int nn=0;
	double sumPrice=0;
	char debugBuffer[1024]={0};

	if(ncit->second.top1.rank!=0x7FFFFFFF){
		double w=ncit->second.top1.weight;
		int p=ncit->second.top1.price;
		sumPrice+=p*(totalProductW/w);
		nn+=1;

	}
	if(ncit->second.top2.rank!=0x7FFFFFFF){
		double w=ncit->second.top2.weight;
		int p=ncit->second.top2.price;
		sumPrice+=p*(totalProductW/w);
		nn+=1;
	}
	if(ncit->second.top3.rank!=0x7FFFFFFF){
		double w=ncit->second.top3.weight;
		int p=ncit->second.top3.price;
		sumPrice+=p*(totalProductW/w);
		nn+=1;
	}
	/*
	int len2=sprintf(debugBuffer,"reTarget[%s],ranks[%d,%d,%d],prices[%d,%d,%d],weights=[%f,%f,%f],totalPrice:%f,numUsed=%d,totalWeight=%f",
		reTarget.c_str(),
		ncit->second.top1.rank,ncit->second.top2.rank,ncit->second.top3.rank,
		ncit->second.top1.price,ncit->second.top2.price,ncit->second.top3.price,
			ncit->second.top1.weight,ncit->second.top2.weight,ncit->second.top3.weight,
			sumPrice,nn,totalProductW);
	debugBuffer[len2]=0;
	MessageBoxA(NULL,debugBuffer,NULL,MB_OK);
	*/
	return int(sumPrice/nn);
}

int CPhonePriceDlg::CalcSupplyPrice(const UnicodeStr& brand,
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
			  Top3Relocation* relocation){
	char buffer[16]={0};
	ValueItem viBrand=defBrandVItem;
	std::map<UnicodeStr,ValueItem>::const_iterator cit=mBrandTable.find(brand);
	if(cit!=mBrandTable.end()){
		viBrand=cit->second;
	}else{
		// MessageBoxW((LPCTSTR)brand.c_str(),L"No brand");
	}
	ValueItem viScreen=defScreenVItem;
	cit=mScreenTable.find(screen);
	if(cit!=mScreenTable.end()){
		viScreen=cit->second;
	}else{
		// MessageBoxW((LPCTSTR)screen.c_str(),L"No Screen");
	}
	ValueItem viPCamera=defPcameraVItem;
	cit=mPCameraTable.find(pcamera);
	// MessageBox(LPCTSTR(pcamera.c_str()));
	if(cit!=mPCameraTable.end()){
		viPCamera=cit->second;
	}else{
		//MessageBoxW((LPCTSTR)pcamera.c_str(),L"No PCamera");
	}
	double standbyW=lookupValue(mStandbyTable,standby,defStandbyW);
	double ramW=lookupValue(mRamTable,ram,defRamW);
	double romW=lookupValue(mRomTable,rom,defRomW);
	double resolveW=lookupValue(mResolveTable,resolve,defResolveW);
	double scameraW=lookupValue(mSCameraTable,scamera,defSCameraW);
	double coreNumW=lookupValue(mCoreNumTable,coreNum,defCoreNumW);
	double cpuFreqW=lookupValue(mCpuTable,cpuFreq,defCpuW);
	double batteryW=lookupValue(mBatteryTable,battery,defBatteryW);
	double networkW=lookupValue(mNetworkTable,network,defNetworkW);
    double totalProductW=viBrand.weight*viScreen.weight*viPCamera.weight;
	totalProductW=totalProductW*standbyW*ramW*romW*resolveW*scameraW*coreNumW*cpuFreqW*batteryW*networkW;
	int len=sprintf(buffer,"%d%d%d",viBrand.targetId,viScreen.targetId,viPCamera.targetId);
	std::string reTarget(buffer,len);
	
	std::map<std::string,Top3Relocation>::const_iterator ncit=mRelocateTable.find(reTarget);
	if(ncit==mRelocateTable.end()){
		// MessageBoxA(NULL,reTarget.c_str(),"No result",MB_OK);
		return 0;
	}
	// MessageBoxA(NULL,reTarget.c_str(),"got result",MB_OK);
	if(relocation){
		*relocation=ncit->second;
	}
	int nn=0;
	double sumPrice=0;
	char debugBuffer[1024]={0};

	if(ncit->second.top1.rank!=0x7FFFFFFF){
		double w=ncit->second.top1.weight;
		int p=ncit->second.top1.supplyPrice;
		sumPrice+=p*(totalProductW/w);
		nn+=1;

	}
	if(ncit->second.top2.rank!=0x7FFFFFFF){
		double w=ncit->second.top2.weight;
		int p=ncit->second.top2.supplyPrice;
		sumPrice+=p*(totalProductW/w);
		nn+=1;
	}
	if(ncit->second.top3.rank!=0x7FFFFFFF){
		double w=ncit->second.top3.weight;
		int p=ncit->second.top3.supplyPrice;
		sumPrice+=p*(totalProductW/w);
		nn+=1;
	}
	/*
	int len2=sprintf(debugBuffer,"reTarget[%s],ranks[%d,%d,%d],prices[%d,%d,%d],weights=[%f,%f,%f],totalPrice:%f,numUsed=%d,totalWeight=%f",
		reTarget.c_str(),
		ncit->second.top1.rank,ncit->second.top2.rank,ncit->second.top3.rank,
		ncit->second.top1.price,ncit->second.top2.price,ncit->second.top3.price,
			ncit->second.top1.weight,ncit->second.top2.weight,ncit->second.top3.weight,
			sumPrice,nn,totalProductW);
	debugBuffer[len2]=0;
	MessageBoxA(NULL,debugBuffer,NULL,MB_OK);
	*/
	return int(sumPrice/nn);
}


CPhonePriceDlg::CPhonePriceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPhonePriceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	defBrandVItem.targetId=0;
	defBrandVItem.weight=10;
	defPcameraVItem.targetId=0;
	defPcameraVItem.weight=10;
	defScreenVItem.targetId=0;
	defScreenVItem.weight=10;
	defStandbyW=defRamW=defRomW=defResolveW=defSCameraW=defCoreNumW=defCpuW=defBatteryW=defNetworkW=10;
}

void CPhonePriceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BRAND, mBrandCombo);
	DDX_Control(pDX, IDC_COMBO_PMDX, mPmdxCombom);
	DDX_Control(pDX, IDC_ZSXT_COMBO, mZsxtCombo);
	DDX_Control(pDX, IDC_SKSD_COMBO, mSksdCmobo);
	DDX_Control(pDX, IDC_RAM_COMBO, mRamCombo);
	DDX_Control(pDX, IDC_ROM_COMBO, mRomCombo);
	DDX_Control(pDX, IDC_PMFBL_COMBO, mPmfblCombo);
	DDX_Control(pDX, IDC_FSXT_COMBO, mFsxtCombo);
	DDX_Control(pDX, IDC_HXS_COMBO, mHxsCombo);
	DDX_Control(pDX, IDC_CPU_COMBO, mCpuCombo);
	DDX_Control(pDX, IDC_DCRL_COMBO, mDcrlCombo);
	DDX_Control(pDX, IDC_WLLX_COMBO, mWllxCombo);
	DDX_Control(pDX, IDC_RICHEDIT22, mDcjgRichEdit);
	DDX_Control(pDX, IDC_RICHEDIT23, mZgjgRichEdit);
	DDX_Control(pDX, IDC_STATIC_RT1, mDBTop1Text);
	DDX_Control(pDX, IDC_RT2_STATIC, mDBTop2Text);
	DDX_Control(pDX, IDC_RT3_STATIC, mDBTop3Text);
}

BEGIN_MESSAGE_MAP(CPhonePriceDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_BRAND, &CPhonePriceDlg::OnCbnSelchangeBrand)
	ON_CBN_SELCHANGE(IDC_COMBO_PMDX, &CPhonePriceDlg::OnCbnSelchangeComboPmdx)
	ON_CBN_SELCHANGE(IDC_ZSXT_COMBO, &CPhonePriceDlg::OnCbnSelchangeZsxtCombo)
	ON_CBN_SELCHANGE(IDC_DCRL_COMBO, &CPhonePriceDlg::OnCbnSelchangeDcrlCombo)
	ON_CBN_SELCHANGE(IDC_WLLX_COMBO, &CPhonePriceDlg::OnCbnSelchangeWllxCombo)
	ON_CBN_SELCHANGE(IDC_SKSD_COMBO, &CPhonePriceDlg::OnCbnSelchangeSksdCombo)
	ON_CBN_SELCHANGE(IDC_RAM_COMBO, &CPhonePriceDlg::OnCbnSelchangeRamCombo)
	ON_CBN_SELCHANGE(IDC_ROM_COMBO, &CPhonePriceDlg::OnCbnSelchangeRomCombo)
	ON_CBN_SELCHANGE(IDC_PMFBL_COMBO, &CPhonePriceDlg::OnCbnSelchangePmfblCombo)
	ON_CBN_SELCHANGE(IDC_FSXT_COMBO, &CPhonePriceDlg::OnCbnSelchangeFsxtCombo)
	ON_CBN_SELCHANGE(IDC_HXS_COMBO, &CPhonePriceDlg::OnCbnSelchangeHxsCombo)
	ON_CBN_SELCHANGE(IDC_CPU_COMBO, &CPhonePriceDlg::OnCbnSelchangeCpuCombo)
	ON_BN_CLICKED(IDC_BUTTON_BTACH, &CPhonePriceDlg::OnBnClickedButtonBtach)
END_MESSAGE_MAP()


// CPhonePriceDlg 消息处理程序

BOOL CPhonePriceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	if (ini_parse("phoneprice.ini", conf_handler, this) < 0) {
		MessageBox(L"Ini Parse Error");
		return FALSE;
	}
	// 主对标参数
	InitFirtRowComboBox(mBrandCombo,mBrandTable);
	InitFirtRowComboBox(mPmdxCombom,mScreenTable);
	InitFirtRowComboBox(mZsxtCombo,mPCameraTable);

	// 辅助参数
	InitSecondRowComboBox(mSksdCmobo,mStandbyTable);
	InitSecondRowComboBox(mRamCombo,mRamTable);
	InitSecondRowComboBox(mRomCombo,mRomTable);
	InitSecondRowComboBox(mPmfblCombo,mResolveTable);
	InitSecondRowComboBox(mFsxtCombo,mSCameraTable);
	InitSecondRowComboBox(mHxsCombo,mCoreNumTable);
	InitSecondRowComboBox(mCpuCombo,mCpuTable);
	InitSecondRowComboBox(mDcrlCombo,mBatteryTable);
	InitSecondRowComboBox(mWllxCombo,mNetworkTable);
	

	CHARFORMAT cf;
	mDcjgRichEdit.GetDefaultCharFormat(cf);
	mZgjgRichEdit.GetDefaultCharFormat(cf);
	//ZeroMemory(&cf,sizeof(CHARFORMAT));
	cf.dwMask = CFM_COLOR|CFM_BOLD; 
	cf.dwEffects &= ~CFE_AUTOCOLOR;
	cf.crTextColor=RGB(255,0,0);  //the text color
	mDcjgRichEdit.SetDefaultCharFormat(cf);
	mZgjgRichEdit.SetDefaultCharFormat(cf);
	//mDcjgRichEdit.SetWindowText(L"");
    UpdatePrice();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPhonePriceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPhonePriceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPhonePriceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

static void GetSelected(const CComboBox& box,UnicodeStr& str ){
	int i=box.GetCurSel();
	CString cstr;
	box.GetLBText(i,cstr);
	str.assign(reinterpret_cast<const UnicodeCharT*>(cstr.GetString()),cstr.GetLength());
}
static void GetRelocateInfoDesc(int order,const RelocateInfo& info,CString& desc){
	desc.Format(L"%ws  零售价格:%d  直供价格:%d  TOP%d",(LPCTSTR)info.phoneName.c_str(),info.price,info.supplyPrice,info.rank);
}
void CPhonePriceDlg::UpdatePrice(){
	char buffer[16]={0};
	UnicodeStr brand;
	GetSelected(mBrandCombo,brand);
	UnicodeStr screen;
	GetSelected(mPmdxCombom,screen);
	UnicodeStr pcamera;
	UnicodeStr standby;
	UnicodeStr ram;
	UnicodeStr rom;
	UnicodeStr resolve;
	UnicodeStr scamera;
	UnicodeStr coreNum;
	UnicodeStr cpuFreq;
	UnicodeStr battery;
	UnicodeStr network;
	GetSelected(mZsxtCombo,pcamera);
	GetSelected(mSksdCmobo,standby);
	GetSelected(mRamCombo,ram);
	GetSelected(mRomCombo,rom);
	GetSelected(mPmfblCombo,resolve);
	GetSelected(mFsxtCombo,scamera);
	GetSelected(mHxsCombo,coreNum);
	GetSelected(mCpuCombo,cpuFreq);
	GetSelected(mDcrlCombo,battery);
	GetSelected(mWllxCombo,network);
	Top3Relocation relocation;

	int price=CalcPrice(brand,screen,pcamera,standby,ram,rom,resolve,scamera,coreNum,cpuFreq,battery,network,&relocation);
	int supplyPrice=CalcSupplyPrice(brand,screen,pcamera,standby,ram,rom,resolve,scamera,coreNum,cpuFreq,battery,network,&relocation);
	CString priceStr;
	CString supplyPriceStr;
	if(price==0){
		priceStr=L"N/A";
	}else{
		priceStr.Format(L"%d",price);
	}
	if(supplyPrice==0){
		supplyPriceStr=L"N/A";
	}else{
		supplyPriceStr.Format(L"%d",supplyPrice);
	}
	mDcjgRichEdit.SetWindowText(priceStr);
	mZgjgRichEdit.SetWindowText(supplyPriceStr);
	CString rtTop1;
	CString rtTop2;
	CString rtTop3;
	if(relocation.top1.rank!=0x7FFFFFFF){
		GetRelocateInfoDesc(1,relocation.top1,rtTop1);
	}
	if(relocation.top2.rank!=0x7FFFFFFF){
		GetRelocateInfoDesc(2,relocation.top2,rtTop2);
	}
	if(relocation.top3.rank!=0x7FFFFFFF){
		GetRelocateInfoDesc(3,relocation.top3,rtTop3);
	}
	mDBTop1Text.SetWindowText(rtTop1);
	mDBTop2Text.SetWindowText(rtTop2);
	mDBTop3Text.SetWindowText(rtTop3);
	this->Invalidate(TRUE);
}
void CPhonePriceDlg::OnCbnSelchangeBrand()
{
	UpdatePrice();
}

void CPhonePriceDlg::OnCbnSelchangeComboPmdx()
{
	UpdatePrice();
}

void CPhonePriceDlg::OnCbnSelchangeZsxtCombo()
{
	UpdatePrice();
}

void CPhonePriceDlg::OnCbnSelchangeDcrlCombo()
{
	UpdatePrice();
}

void CPhonePriceDlg::OnCbnSelchangeWllxCombo()
{
	UpdatePrice();
}

void CPhonePriceDlg::OnCbnSelchangeSksdCombo()
{
	UpdatePrice();
}

void CPhonePriceDlg::OnCbnSelchangeRamCombo()
{
	UpdatePrice();
}

void CPhonePriceDlg::OnCbnSelchangeRomCombo()
{
	UpdatePrice();
}

void CPhonePriceDlg::OnCbnSelchangePmfblCombo()
{
	UpdatePrice();
}

void CPhonePriceDlg::OnCbnSelchangeFsxtCombo()
{
	UpdatePrice();
}

void CPhonePriceDlg::OnCbnSelchangeHxsCombo()
{
	UpdatePrice();
}

void CPhonePriceDlg::OnCbnSelchangeCpuCombo()
{
	UpdatePrice();
}

bool ConvertToANSI(LPCTSTR src,int len,std::string& dest){
	int destLen=len*2;
	LPSTR destBuffer=new char[destLen];
	int nn=WideCharToMultiByte(
		CP_ACP,
		0,
		src,
		len,
		destBuffer,
		destLen,
		NULL,
		NULL
		);
	dest.assign(destBuffer,nn);
	delete[] destBuffer;
	return TRUE;
}
void CPhonePriceDlg::OnBnClickedButtonBtach()
{
	CFileDialog FileDialog(TRUE,
		L"*.*",
		NULL,
		OFN_HIDEREADONLY,
		L"Excel Files: (*.xls)|*.xls||");

	if(FileDialog.DoModal() != IDOK)
	{
		return;
	}
	CString pName = FileDialog.GetPathName();
	CApplication app;
	CWorkbooks books;
	CWorkbook book;
	CWorksheets sheets;
	CWorksheet sheet;
	CRange range;
	CRange iCell;
	LPDISPATCH lpDisp;
	COleVariant vResult;
	CRange usedRange;
	CRange eleRange;
	CScreenNumberHandler screenHandler;
	CPCameraNumberHandler pcameraHandler;
	CSCameraNumberHandler scameraHandler;
	CRamNumberHandler  ramHandler;
	CRomNumberHandler romHandler;
	CStandbyNumberHandler standbyHandler;
	CResolveNumberHandler resolveHandler;
	CCoreNumNumberHandler coreNumHandler;
	CCpuFreqNumberHandler cpuFreqHandler;
	CBatteryNumberHandler batteryHandler;
	FILE* fout=fopen("./output.csv","w");
	if(fout==NULL){
		MessageBox(L"Can't open file 'output.csv' for write");
		return ;
	}
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if(!app.CreateDispatch(L"Excel.Application"))
	{
		AfxMessageBox(L"无法启动Excel服务器!");
		return;
	}
	books.AttachDispatch(app.get_Workbooks());
	lpDisp = books.Open(pName,covOptional, covOptional, covOptional, covOptional, covOptional,covOptional, covOptional, covOptional, covOptional, covOptional,covOptional, covOptional, covOptional,covOptional);
	
	//得到Workbook
	book.AttachDispatch(lpDisp);
	//得到Worksheets
	sheets.AttachDispatch(book.get_Worksheets());
 
	//得到当前活跃sheet
	//如果有单元格正处于编辑状态中，此操作不能返回，会一直等待
	lpDisp=book.get_ActiveSheet();
	sheet.AttachDispatch(lpDisp);
	usedRange.AttachDispatch(sheet.get_UsedRange());
	range.AttachDispatch(usedRange.get_Rows());
	long rows=range.get_Count();
	range.AttachDispatch(usedRange.get_Columns());
	long cols=range.get_Count();
	range.ReleaseDispatch();
	usedRange.ReleaseDispatch();
	//读取单元格的值
	range.AttachDispatch(sheet.get_Cells());
	CString wheader;
	wheader=L"\"价格\",\"手机型号\",\"对标1\",\"对标2\",\"对标3\"";
	std::string header;
	ConvertToANSI(wheader.GetString(),wheader.GetLength(),header);
	fprintf(fout,"%s\n",header.c_str());
	for(int r=2;r<=rows;r++){
		UnicodeStr screen;
		UnicodeStr pcamera;
		UnicodeStr scamera;
		UnicodeStr ram;
		UnicodeStr rom;
		UnicodeStr standby;
		UnicodeStr resolve;
		UnicodeStr coreNum;
		UnicodeStr cpuFreq;
		UnicodeStr battery;
		UnicodeStr network;
		UnicodeStr brand;
		UnicodeStr typeName;
		Top3Relocation relocation;
		for(int c=1;c<cols;c++){
			eleRange.AttachDispatch(range.get_Item (COleVariant((long)r),COleVariant((long)c)).pdispVal );
			/*COleVariant*/ vResult =eleRange.get_Value2();
			vResult.ChangeType(VT_BSTR);
			CString str=vResult.bstrVal;
			CString todoStr;
			if(c==2){
				brand.assign((const UnicodeCharT*)str.GetString(),str.GetLength());
				std::map<UnicodeStr,UnicodeStr>::const_iterator bit=mBrandMapTable.find(brand);
				if(bit!=mBrandMapTable.end()){
					brand.assign(bit->second);
				}
			}else if(c==3){
				typeName.assign((const UnicodeCharT*)str.GetString(),str.GetLength());
			}else if(c==9){
				screenHandler.NormanizeString(str,todoStr);
				screen.assign((const UnicodeCharT*)todoStr.GetString(),todoStr.GetLength());
			}else if(c==10){
				pcameraHandler.NormanizeString(str,todoStr);
				pcamera.assign((const UnicodeCharT*)todoStr.GetString(),todoStr.GetLength());
			}else if(c==11){
				scameraHandler.NormanizeString(str,todoStr);
				scamera.assign((const UnicodeCharT*)todoStr.GetString(),todoStr.GetLength());
			}else if(c==12){
				ramHandler.NormanizeString(str,todoStr);
				ram.assign((const UnicodeCharT*)todoStr.GetString(),todoStr.GetLength());
			}else if(c==13){
				romHandler.NormanizeString(str,todoStr);
				rom.assign((const UnicodeCharT*)todoStr.GetString(),todoStr.GetLength());
			}else if(c==14){
				standbyHandler.NormanizeString(str,todoStr);
				standby.assign((const UnicodeCharT*)todoStr.GetString(),todoStr.GetLength());
			}else if(c==15){
				resolveHandler.NormanizeString(str,todoStr);
				resolve.assign((const UnicodeCharT*)todoStr.GetString(),todoStr.GetLength());
			}else if(c==16){
				coreNumHandler.NormanizeString(str,todoStr);
				coreNum.assign((const UnicodeCharT*)todoStr.GetString(),todoStr.GetLength());
			}else if(c==17){
				cpuFreqHandler.NormanizeString(str,todoStr);
				cpuFreq.assign((const UnicodeCharT*)todoStr.GetString(),todoStr.GetLength());
			}else if(c==18){
				batteryHandler.NormanizeString(str,todoStr);
				battery.assign((const UnicodeCharT*)todoStr.GetString(),todoStr.GetLength());
			}
			else if(c==19){
				batteryHandler.NormanizeString(str,todoStr);
				network.assign((const UnicodeCharT*)todoStr.GetString(),todoStr.GetLength());
			}
			// TODO add network handler.
			eleRange.ReleaseDispatch();

		}
		CString name;
		name.Format(L"%s %s",(LPCTSTR)brand.c_str(),(LPCTSTR)typeName.c_str());
		std::string str0;
		ConvertToANSI(name.GetString(),name.GetLength(),str0);
		int price=CalcPrice(brand,screen,pcamera,standby,ram,rom,resolve,scamera,coreNum,cpuFreq,battery,network,&relocation);
		if(price==0){
			fprintf(fout,"N/A,\"%s\",,,\n",str0.c_str());
		}else{
			CString rtTop1;
			CString rtTop2;
			CString rtTop3;
			if(relocation.top1.rank!=0x7FFFFFFF){
				GetRelocateInfoDesc(1,relocation.top1,rtTop1);
			}
			if(relocation.top2.rank!=0x7FFFFFFF){
				GetRelocateInfoDesc(2,relocation.top2,rtTop2);
			}
			if(relocation.top3.rank!=0x7FFFFFFF){
				GetRelocateInfoDesc(3,relocation.top3,rtTop3);
			}
			std::string str1;
			std::string str2;
			std::string str3;			
			
			/*
			StringUtil::u16tou8(name.c_str(),name.size(),str0);
			StringUtil::u16tou8((const UnicodeCharT*)(rtTop1.GetString()),rtTop1.GetLength(),str1);
			StringUtil::u16tou8((const UnicodeCharT*)(rtTop2.GetString()),rtTop2.GetLength(),str2);
			StringUtil::u16tou8((const UnicodeCharT*)(rtTop3.GetString()),rtTop3.GetLength(),str3);
			*/
			
			ConvertToANSI(rtTop1.GetString(),rtTop1.GetLength(),str1);
			ConvertToANSI(rtTop2.GetString(),rtTop2.GetLength(),str2);
			ConvertToANSI(rtTop3.GetString(),rtTop3.GetLength(),str3);
			fprintf(fout,"%d,\"%s\",\"%s\",\"%s\",\"%s\"\n",price,str0.c_str(),str1.c_str(),str2.c_str(),str3.c_str());
		}
		
		

	}
	fclose(fout);
    
	//释放对象  
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.Close(covOptional,COleVariant(pName),covOptional);
	books.Close(); 
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.Quit();
	app.ReleaseDispatch();
	
	// 退出

	OnOK();
}

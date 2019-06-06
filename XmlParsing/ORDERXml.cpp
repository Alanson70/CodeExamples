#include "ORDERXml.hpp"
#include "xerces_utils.hpp"

#include "cotokens.hpp"
#include "OrderLoader.hpp"

#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/parsers/SAXParser.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

using namespace xercesc;

#define FIX_OFFSET(x) ((x) - 1)
 // �������� ����� ��� �������� �������� �� ��������� ����������� �� 1 ������ ��� �� ����� ����, FIX_OFFSET �� ��������
const OFFLEN OI_BID    					={ FIX_OFFSET(5),	3	};
const OFFLEN OI_CommissionNumber 		={ FIX_OFFSET(8),	6	};
const OFFLEN OI_CommisionNumberYear     ={ FIX_OFFSET(14),	4	};
const OFFLEN OI_PartnerKey    		    ={ FIX_OFFSET(24),	9	};
const OFFLEN OI_OrderStatus    			={ FIX_OFFSET(55),	4	};
const OFFLEN OI_ModelYear    			={ FIX_OFFSET(59),	4	};
const OFFLEN OI_SalesProgram    		={ FIX_OFFSET(63),	3	};
const OFFLEN OI_ModelVersion    		={ FIX_OFFSET(66),	1	};
const OFFLEN OI_ProductBrand    		={ FIX_OFFSET(67),	1	};
const OFFLEN OI_ModelCoding    			={ FIX_OFFSET(68),	6	};
const OFFLEN OI_ColourFinishCode    	={ FIX_OFFSET(74),	2	};
const OFFLEN OI_ColourTopCode    		={ FIX_OFFSET(76),	2	};
const OFFLEN OI_InteriorCode    		={ FIX_OFFSET(78),	2	};
const OFFLEN OI_FeaturesEG    			={ FIX_OFFSET(384), 240	};
const OFFLEN OI_FeaturesL    			={ FIX_OFFSET(624), 120	};
const OFFLEN OI_IFAOrderType    		={ FIX_OFFSET(884), 1	};
const OFFLEN OI_IFATimingIndicator    	={ FIX_OFFSET(885), 1	};
const OFFLEN OI_DesiredSGW    			={ FIX_OFFSET(886), 6	};
const OFFLEN OI_ConfirmedSGW    		={ FIX_OFFSET(898), 6	};
const OFFLEN OI_SpecialAction    		={ FIX_OFFSET(937), 1	};
const OFFLEN OI_ProductionNumberYear    ={ FIX_OFFSET(949), 4	};
const OFFLEN OI_ProductionNumberWeek    ={ FIX_OFFSET(953), 2	};
const OFFLEN OI_ProductionNumberDay    	={ FIX_OFFSET(955), 1	};
const OFFLEN OI_ProductionNumberID    	={ FIX_OFFSET(956), 4	};
const OFFLEN OI_Factory    				={ FIX_OFFSET(960), 2	};
const OFFLEN OI_VIN_BODY    			={ FIX_OFFSET(962), 10	};
const OFFLEN OI_VIN    					={ FIX_OFFSET(972), 17	};
const OFFLEN OI_EngineNo    			={ FIX_OFFSET(989), 10	};
const OFFLEN OI_TrackingPoints    		={ FIX_OFFSET(999), 9	};
const OFFLEN OI_EnginePowerIndex    	={ FIX_OFFSET(1499),1	};
	
const OFFLEN IV_BID    					={ FIX_OFFSET(5),	3	};
const OFFLEN IV_CommissionNumber    	={ FIX_OFFSET(8),	6	};
const OFFLEN IV_CommisionNumberYear    	={ FIX_OFFSET(14),	4	};
const OFFLEN IV_PriceTotal    			={ FIX_OFFSET(58),	13	};
const OFFLEN IV_PriceModel    			={ FIX_OFFSET(84),	13	};
const OFFLEN IV_PriceColour    			={ FIX_OFFSET(97),	13	};
const OFFLEN IV_Prices    				={ FIX_OFFSET(110), 4250};

const OFFLEN FS_Features    			={ FIX_OFFSET(71),	1500};
const OFFLEN FS_VIN    					={ FIX_OFFSET(1571),17	};

const char* ORDER_BEGINNING_TAG = "SyncOrder";
const char* ORDERS_MAIN_TAG		= "tns:Orders";

const char* XSD_EXTERNAL_NAMESPACE="";
const char* XSD_FILENAME="NewCarsOrderNotificationService.xsd";




////////////////////////////////////////////////////
// ���������� ������ ��� ������� ��� ���������
///////////////////////////////////////////////////
class XMLErrorHandler	: xercesc::ErrorHandler
{
public:    
    XMLErrorHandler();
    
    virtual void	warning(const xercesc::SAXParseException& exc);
    virtual void	error(const xercesc::SAXParseException& exc);
    virtual void	fatalError(const xercesc::SAXParseException& exc);

    virtual void	resetErrors();

	std::string		getErrorString() const { return m_error_string; }

private :
    bool			m_IsErrors;
	std::string		m_error_string;
};

//////////////////////////////////////////////////
// ������� XML 
///////////////////////////////////////////////////

const int MAX_QNAME_LEN = 50; // ��� ����������� �������� ��������� � ������� ��������� � ��� ��������

class XMLElement
{
public :
	XMLElement(const XMLElement *p_prev, const	XMLCh* const p_qname);
	~XMLElement();

	void	text(const   XMLCh* const   p_text, const   XMLSize_t length)  const; 

	const char			*name()  const;   // ������ ���
	const char			*qname() const;   // ������ ��� � Namespace 
	const char			*text()  const;   // �����
	const XMLElement	*parent()  const; // ���������� ������� (������������)	
	
private:	
	char				 m_qname[MAX_QNAME_LEN]; 
	mutable char*    	 m_text;	 

	const XMLElement	 *mp_parent;	
};

///////////////////////////////////////////////////
// ���������� ����������� (����� �������� � ������)
///////////////////////////////////////////////////
class XMLContentHandler : public DefaultHandler 
{	
public:
	typedef enum
	{
		XML_START_ELEM,
		XML_END_ELEM,
		XML_TEXT
	}XMLSteps;

public:
	XMLContentHandler(void);
	~XMLContentHandler();

	void startElement(
		const   XMLCh* const    p_uri,
		const   XMLCh* const    p_name,
		const   XMLCh* const    p_qname,
		const   Attributes&     r_attrs
	);
	void endElement(
		const   XMLCh* const    p_uri,
		const   XMLCh* const    p_name,
		const   XMLCh* const    p_qname
	);
	void characters(
		const   XMLCh* const    p_chars,
		const   XMLSize_t       length
	);
	
	const XMLElement *getElement()	    const	{ return mp_current; } // ������� ������� ��������
	int getStep()						const	{ return m_step; }     // ������� ���: ������ ��������, �����, �����
	bool isAncestor(const char *qName)  const;							// ����� ������� ������� ����� ����� �������, ������� � ����
	bool isError()						const	{ return m_isError; }
	
private:

	const XMLElement			*mp_current;		// ������� �������, � ������� ��������
	const XMLElement			*mp_lastCurrent;	// �������, ������� ����� ������� ����� �������� � ������ ��� �����������
	int							m_step;				// ��. XMLSteps: 0 - ������ ����, 1 - ����� ����, 2 - ������ ������
	bool						m_isError;			// ������, ������������ ��� ���������
};

///////////////////////////////////////////////////////  ����������  /////////////////////////////////////////////////////////


////////////////////////////////////////////////////
// ���������� ������ ��� ������� ��� ���������
///////////////////////////////////////////////////
XMLErrorHandler::XMLErrorHandler()	: m_IsErrors(false)
{
}

void XMLErrorHandler::warning(const xercesc::SAXParseException& exc)
{
    m_IsErrors = true;	
	xercesc_utils::XmlString l_msg = exc.getMessage();
	std::stringstream ss;
	ss << "��������: ������ = " << exc.getLineNumber() << ", ������� = " << exc.getColumnNumber() << ", ���������: " << l_msg.getString();
	m_error_string = ss.str();
}

void XMLErrorHandler::error(const xercesc::SAXParseException& exc)
{
    m_IsErrors = true;
	xercesc_utils::XmlString l_msg = exc.getMessage();
	std::stringstream ss;
	ss << "������: ������ = " << exc.getLineNumber() << ", ������� = " << exc.getColumnNumber() << ", ���������: " << l_msg.getString();
	m_error_string = ss.str();
}

void XMLErrorHandler::fatalError(const xercesc::SAXParseException& exc)
{
    m_IsErrors = true;
	xercesc_utils::XmlString l_msg = exc.getMessage();
	std::stringstream ss;
	ss << "��������� ������: ������ = " << exc.getLineNumber() << ", ������� = " << exc.getColumnNumber() << ", ���������: " << l_msg.getString();
	m_error_string = ss.str();
}

void XMLErrorHandler::resetErrors()
{
	m_IsErrors = false;
	m_error_string.clear();
}


//////////////////////////////////////////////////
// ������� XML 
///////////////////////////////////////////////////
XMLElement::XMLElement(const XMLElement *p_prev, const	XMLCh* const p_qname) :
	mp_parent(p_prev)
	,m_text(nullptr)
{	
	XMLString::transcode(p_qname, m_qname, MAX_QNAME_LEN);
}
	
XMLElement::~XMLElement()
{
	delete m_text;	
}

void XMLElement::text(const   XMLCh* const   p_text, const   XMLSize_t length)  const
{		
	if((1 == length) && ('\n' == p_text[0])) // ���������� �������� �� ����� ������
	{
		return;
	}

	if(!m_text)
	{
		m_text = new char[length+1];
		XMLString::transcode(p_text, m_text, length);
	}
}

const char *XMLElement::qname() const
{
	return m_qname;
}

const char *XMLElement::text() const
{
	return m_text;
}

const XMLElement *XMLElement::parent() const
{
	return mp_parent;
}

///////////////////////////////////////////////////
// ���������� ����������� (����� �������� � ������)
///////////////////////////////////////////////////
XMLContentHandler::XMLContentHandler(void) : 
	 mp_current(nullptr)
	,mp_lastCurrent(nullptr)
	,m_step(0)
	,m_isError(false)
{	
}
	 
XMLContentHandler::~XMLContentHandler()
{
	if(mp_lastCurrent) // ��������� ����� end-���� ������� ���������� ��������������, �� ������� ��� ��� ������ �� �����������
	{
		delete mp_lastCurrent;
	}	
}

// ���� ��� ����� �������, ������� � ����
bool XMLContentHandler::isAncestor( const char *p_qname ) const
{
	for(auto el=mp_current ; el!=nullptr ; el=el->parent())
	{
		if(0 == strcmp(el->qname(),p_qname)) return true;
	}
	return false;	
}

void XMLContentHandler::startElement(	const   XMLCh* const    uri,
										const   XMLCh* const    localname,
										const   XMLCh* const    qname,
										const   Attributes&     attrs)
{		
	m_step = XML_START_ELEM;
		
	if(mp_lastCurrent) // ������� �������, ���������� � ��������
	{
		mp_current = mp_lastCurrent->parent();
		delete mp_lastCurrent;
		mp_lastCurrent = nullptr;
	}

	mp_current = new XMLElement( mp_current,  qname ); // ������� �������, �������� ��������
}

void XMLContentHandler::endElement(	const   XMLCh* const    uri,
									const   XMLCh* const    localname,
									const   XMLCh* const    qname)
{
	m_step = XML_END_ELEM;

	if(mp_lastCurrent == mp_current) // ��������� ������� ������� � ��������, ������ ��� �� ��������
	{
		mp_current = mp_lastCurrent->parent();
	}

	if(mp_lastCurrent) // ������� �������, ���������� � ��������
	{
		delete mp_lastCurrent;
		mp_lastCurrent = nullptr;
	}
	
	mp_lastCurrent = mp_current; // ����� ���� ������� �� ��� ��������� �������� � ������� ��������� �� ���������� ����, � ����� ������ ������� ���
}

void XMLContentHandler::characters(	const   XMLCh* const    chars,
									const   XMLSize_t       length)
{	
	m_step = XML_TEXT;

	mp_current->text( chars, length );
}

////////////////////////////////////////////////////
/// ��������� ������-�������
////////////////////////////////////////////////////
ORDERXml *ORDERXml::CreateORDERXml(const char *p_xmlFile)
{
	return new ORDERXml(p_xmlFile);
}

ORDERXml::ORDERXml(const char *ppFileName) : 
	 mp_parser(nullptr)
	,mp_handler(nullptr)
	,mp_scanToken(nullptr)
	,m_orderNum(-1)
	,m_fileName(ppFileName)
	,m_isValid(false)
{	
	try
	{
		xercesc::XMLPlatformUtils::Initialize();
	}
	catch( const xercesc::XMLException &exc )
	{		
		xercesc_utils::XmlString l_msg = exc.getMessage();
		m_errorString = "������ ������������� xercesc XML: ";
		m_errorString += l_msg.getString();
		m_isValid = false;		
		return;
	}	
	mp_parser = XMLReaderFactory::createXMLReader();
	mp_handler = new XMLContentHandler();
	mp_scanToken = new XMLPScanToken();
}

ORDERXml::~ORDERXml()
{
	delete mp_scanToken;
	delete mp_handler;
	delete mp_parser;

	xercesc::XMLPlatformUtils::Terminate();
}

/* ��������� ������ ��� (� �.�. ����) ��� ��������� xsd ����� */
std::string ORDERXml::formXsdFileName(const std::string &p_xsdFilePath, const char *pp_newFileName)
{
	boost::filesystem::path lPath(p_xsdFilePath);
	std::stringstream ss;
	if (0 == lPath.string().size())
	{
		ss << "../xsd/";
	}
	else
	{
		ss << lPath.generic_string() << "/";
	}
	ss << pp_newFileName;
	return ss.str();
}
//////////////////////////////////////////////////////////////////////////

bool ORDERXml::validate(const char *xmlFile,const char *xsdFile, const char *extLink)
{   
	IFUNCTRACE_DEVELOP();
	    
	XMLErrorHandler handler;
		
	mp_parser->setErrorHandler((ErrorHandler *)&handler);
	if(nullptr != xsdFile)
	{
		mp_parser->loadGrammar(xsdFile, xercesc::Grammar::SchemaGrammarType, true);
		mp_parser->setFeature(xercesc::XMLUni::fgXercesUseCachedGrammarInParse, true);
		mp_parser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);       // ���������� ��������� �� XSD

		// ������ DOM setExternalSchemaLocation
		std::stringstream ss;
		ss <<(XSD_EXTERNAL_NAMESPACE);
		ss << boost::filesystem::path(xsdFile).filename().generic_string();
		auto l_property = std::unique_ptr<XMLCh>(XMLString::transcode(ss.str().c_str()));
		mp_parser->setProperty(XMLUni::fgXercesSchemaExternalSchemaLocation, l_property.get());		
	}	
	mp_parser->setExitOnFirstFatalError(true);
	mp_parser->setValidationConstraintFatal( true );	// ��� ������ �� ������ �������, ���������� ������
	
	try
	{
		mp_parser->parse( xmlFile);

		if( 0 != mp_parser->getErrorCount() )
		{
			m_errorString = "������ ��������� XML: ";
			m_errorString += handler.getErrorString();
			ITRACE_DEVELOP(m_errorString.c_str());
			return false;
		}
    }
    catch (const xercesc::XMLException& exc )
	{			
		xercesc_utils::XmlString l_msg = exc.getMessage();
		m_errorString = "��������� ���������� XML: ";
		m_errorString += l_msg.getString();
		ITRACE_DEVELOP("��������� ����������: \n");
		ITRACE_DEVELOP(l_msg.getString());
        return false;
    }
    catch (const xercesc::SAXParseException& exc)
	{		
		xercesc_utils::XmlString l_msg = exc.getMessage();
		m_errorString = "��������� ���������� SAX-�������(SAXParseException): ";
		m_errorString += l_msg.getString();
		ITRACE_DEVELOP("��������� ����������: \n");
		ITRACE_DEVELOP(l_msg.getString());
        return false;
    }
    catch (const xercesc::OutOfMemoryException &exc)
	{		
		xercesc_utils::XmlString l_msg = exc.getMessage();
		m_errorString = "��������� ���������� �������� ������ (OutOfMemoryException): ";
		m_errorString += l_msg.getString();
		ITRACE_DEVELOP("��������� ����������: \n");
		ITRACE_DEVELOP(m_errorString.c_str());
        return false;
    }
    catch (...)
	{
		m_errorString = "�������������� ���������� xercesc";
		ITRACE_DEVELOP(m_errorString.c_str());
        return false;
    }
		
	// ���������� ��������, ������������� ������ ��� ��������	
	mp_parser->loadGrammar("", xercesc::Grammar::SchemaGrammarType, false); // ��� ����� ����� ��������� ������� �� 80 �� 400%, ������, �������� ������ � ������� First-chance exeption,
																			// �������,�������, ���� ����� �� ������ �� ������� (msdn)  
	mp_parser->setFeature(xercesc::XMLUni::fgXercesUseCachedGrammarInParse, false);
	mp_parser->setProperty(XMLUni::fgXercesSchemaExternalSchemaLocation,  nullptr);
	mp_parser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, false);
	mp_parser->setErrorHandler((ErrorHandler *)mp_handler);	
	
	mp_parser->setFeature(xercesc::XMLUni::fgXercesCalculateSrcOfs,false); // ������������ ����������� ������������������

	mp_parser->setContentHandler(mp_handler);	

	return true;
}

bool ORDERXml::parseFile()
{		
	/* xsd ���� ����� � ��������, ��������� � main.ini */
	std::string	 l_xsdFilePath = ILoaderObject::getXsdFilePath();

	/* ���� � XSD ������ �� main.ini */
	std::string	 l_xsdFileName = formXsdFileName(l_xsdFilePath.c_str(),XSD_FILENAME);

	m_isValid = validate(m_fileName.c_str(),l_xsdFileName.c_str());

	if(!m_isValid)		
	{
		return m_isValid;
	}

	return startParseSyncOrder();	
}

/* ������� � ���������� ������ */
bool ORDERXml::goToNextOrder()
{	
	if(true == gotoNextSyncOrder())
	{
		return fillBuffers();
	}	
	return false;
}

/* ���������� ������ ������������� ���� */
bool ORDERXml::getLine(IDataAggregationRecordType pType, std::string &pBuffer)
{		
	switch(pType)
	{
		case dartOI :		
			pBuffer.assign(m_bufferOI,sizeof(m_bufferOI));		
		break;

		case dartIV :
			pBuffer.assign(m_bufferIV,sizeof(m_bufferIV));
		break;
	
		case dartFS :
			pBuffer.assign(m_bufferFS,sizeof(m_bufferFS));
		break;		
	}
	return true;
}


/////////////////// ���������� ������� ������� ////////////////////////////

inline bool ORDERXml::isMatchedTheStartOf( const char *p_sampleTag, const char *p_qname, int n_step ) 
{
	return (( 0 == strcmp( p_qname, p_sampleTag )) && ( XMLContentHandler::XML_START_ELEM == n_step )); 
}

inline bool ORDERXml::isMatchedTheEndOf( const char *p_sampleTag, const char *p_qname, int n_step) 
{
	return (( 0 == strcmp( p_qname, p_sampleTag )) && ( XMLContentHandler::XML_END_ELEM == n_step ));
};

inline bool ORDERXml::isMatchedTheEndOf( const char *p_sampleTag, const char *p_sampleParentTag, const char *p_qname, int n_step) 
{
	return (( 0 == strcmp(p_qname, p_sampleTag )) && ( mp_handler->isAncestor(p_sampleParentTag)) && ( XMLContentHandler::XML_END_ELEM == n_step ));
};

inline void ORDERXml::copyByLocation(char *p_buffer, const char *p_text, const OFFLEN &r_location)
{		
	if(p_buffer)
	{
		memcpy(p_buffer+r_location.offset, p_text, std::min<long>(r_location.len,strlen(p_text)));
	}
};	

bool ORDERXml::startParseSyncOrder()
{		
	m_orderNum=-1;	
	
	if(mp_parser->parseFirst( m_fileName.c_str(), *mp_scanToken))
	{	
		m_orderNum=0;	
	}
	else
	{		
		m_errorString = "�� ������ ������ ������� XML";
		m_isValid = false;
	}
	return m_isValid;
}

bool ORDERXml::gotoNextSyncOrder()
{	
	assert(0 <= m_orderNum); // ������ ������ ���� ������ ��� ������
	
	while(mp_parser->parseNext( *mp_scanToken ))
	{			
		auto l_qname = mp_handler->getElement()->qname();
		auto l_step =  mp_handler->getStep();

		if(isMatchedTheStartOf(ORDER_BEGINNING_TAG, l_qname, l_step))
		{
			m_orderNum++;

			return true;
		}

		if( isMatchedTheEndOf( ORDERS_MAIN_TAG, l_qname, l_step))
		{		
			m_orderNum = -1;		
		}
	}
	return false;
}


bool ORDERXml::fillBuffers()
{ 			
	assert(m_isValid); // ���� ���� ��������� ������ - ��� ��� �� ������ ����

	// ��������� ��� �������������� �������� � ���������� ������ � ������� ���������
	struct DealerRef
	{
		struct Item
		{
			char	Country[4];
			char	Brand;
			char	PartnerNumber[6];
		};		
		static void initItem(Item *ppItem)
		{
			memset (ppItem, 0, sizeof(Item));
		}
	};
	DealerRef::Item	l_dealerRef={0};

	struct Feature
	{
		struct Item
		{
			bool	IsBuiltIn;
			char	PRType;
			char	PRFamily[4];
			char	PRNumber[4];
			bool	IsStandard;
			bool	IsPackage;
		};
		
		static void initItem(Item *ppItem)
		{
			memset (ppItem, 0, sizeof(Item));
		}
	};
	Feature::Item				l_feature = {0};    // ������� ��������� ������������
	std::vector<Feature::Item>	l_featuresEGvec;	// ������������ EG
	std::vector<Feature::Item>	l_featuresLvec;		// ������������ L
	std::vector<Feature::Item>	l_featuresAllvec;   // ��� ������������

	auto featuresToStringStream = [](const std::vector<Feature::Item> &f, unsigned int maxSize) ->std::stringstream
	{			
		std::stringstream ss;

		for (auto iter = f.cbegin(); iter != f.cend(); ++iter)
		{				
			if(maxSize>0 &&  ((ss.str().size() + 4) > maxSize)) /* ���� �������� ����� � ������, ��������� ���� ����� */
			{
				break;
			}
			if (ss.str().size())
			{
				ss << ' ';
			}
			ss << iter->PRNumber;
		}
		return ss;
	};
		
	struct TrackingPoint
	{
		struct Item
		{
			char	TrackingPointNumber[21];						// [1]		����� ����-������ (CL01357)
			char	ReachedDate[33];								// [0..1]	���� ���������� ����� ����-������
			char	ReachedTime[33];								// [0..1]	����� ���������� ����� ����-������
			char	PlannedImporterDate[33];						// [0..1]	����������� ���� ���������� ����� ����-������
			char	PlannedImporterTime[33];						// [0..1]	����������� ����� ���������� ����� ����-������
			char	CurrentETA[33];									// [0..1]	����������� ����� �������� � ���� ����-����� � ������
			char	PreviousETA[33];								// [0..1]	���������� ������������ ����� �������� � ���� ����-����� � ������
			char	FirstETA[33];									// [0..1]	������ ������������ ����� �������� � ���� ����-�����
			bool	ETAWarning;										// [0..1]	������� ����, ��� ���� ����-����� ����� ���� ������������
			char	ContractNumber[256];							// [0..1]	����� ��������� � ������������
			char	ContractPrintedDate[33];						// [0..1]	����� ������ ��������� � ������������
			bool	IsCurrentIndicator;								// [0..1]	��������� �������� ����-������ ������
			char	ProcessingTimestamp[33];						// [0..1]	�������� ����� ��������� ����-������ (����� ���������� �� ReachedDate)	
		};
		
		static void initItem(Item *ppItem)
		{
			memset (ppItem, 0, sizeof(Item));
		}
	};
	
	TrackingPoint::Item			l_trackingPoint = {0};
	std::vector<TrackingPoint::Item>	l_trackingPointsVec;
		
	struct Price
	{
		struct Item
		{
			char	PriceGroup[33];		// ns3:PriceGroup
			char	PriceType[33];		// ns3:PriceType
			char	Reference[4];		// ns3:Reference
			char	Currency[4];	    // ������� currency="RUB"
			long long	Amount;			// ns3:Amount		
		};
		
		static void initItem(Item *ppItem)
		{
			memset (ppItem, 0, sizeof(Item));
		}
	};

	Price::Item					l_price = {0};
	std::vector<Price::Item>	l_pricesVec;

	bool l_priceSavedTotal = false;
	bool l_priceSavedModel = false;
	bool l_priceSavedColor = false;	
	
	// ����� �������������
	

	// ������� ������
	memset(m_bufferOI,' ',sizeof(m_bufferOI));
	memcpy(m_bufferOI,"OI06",4);
	m_bufferOI[sizeof(m_bufferOI)-1] = '+';
	
	memset(m_bufferIV,' ',sizeof(m_bufferIV));
	memcpy(m_bufferIV,"IV06",4);
	m_bufferIV[sizeof(m_bufferIV)-1] = '+';
	
	memset(m_bufferFS,' ',sizeof(m_bufferFS));
	memcpy(m_bufferFS,"FS",2);
	m_bufferFS[sizeof(m_bufferFS)-1] = '+';	
	
	// ���� �� ���� ����� �� ����� ������
	while(mp_parser->parseNext(*mp_scanToken))
	{			
		auto l_step = mp_handler->getStep();

		if(XMLContentHandler::XML_END_ELEM != l_step) // ��� ���������� ������ ����������� ����
		{
			continue;
		}

		auto l_elem = mp_handler->getElement();
		auto l_qname = l_elem->qname();
		if( isMatchedTheEndOf( ORDER_BEGINNING_TAG, l_qname, l_step)) 
		{
			return true;
		}
		auto l_text = l_elem->text();
		if(nullptr == l_text) 
		{
			l_text = "";
		}

		//////////// ��������� ���������, ����� ��� ���� ����� ���������� ////////////////////////
		// features - ����� �������������

		bool isFound = true; // ����������, ��� ������ ����� �� ����� �������� ��� �� ������
		
		if( isMatchedTheEndOf( "ns9:IsBuiltIn", l_qname, l_step))
		{
			l_feature.IsBuiltIn=(l_text=="true");
		}
		else
		if( isMatchedTheEndOf( "ns9:PRType", l_qname, l_step))
		{
			l_feature.PRType=l_text[0];
		}
		else
		if( isMatchedTheEndOf( "ns9:PRFamily", l_qname, l_step))
		{
			memcpy( (char *)&(l_feature.PRFamily) , l_text,sizeof(l_feature.PRNumber));		
		}
		else
		if( isMatchedTheEndOf( "ns9:PRNumber", l_qname, l_step))
		{
			memcpy( (char *)&(l_feature.PRNumber) , l_text,sizeof(l_feature.PRNumber));		
		}
		else
		if( isMatchedTheEndOf( "ns9:IsStandard", l_qname, l_step))
		{
			l_feature.IsStandard=(l_text=="true");			
		}
		else
		if( isMatchedTheEndOf( "ns9:IsPackage", l_qname, l_step))
		{
			l_feature.IsPackage=(l_text=="true");		
		}		
		else
		if( isMatchedTheEndOf( "ns9:Feature", l_qname, l_step))
		{
			l_featuresAllvec.push_back(l_feature);

			if('L'==l_feature.PRType)
			{
				l_featuresLvec.push_back(l_feature);
			}				
			else
			if('E'==l_feature.PRType || 'G'==l_feature.PRType)
			{
				l_featuresEGvec.push_back(l_feature);
			}	
			Feature::initItem(&l_feature); // �������� ������������� ��������� ��� ������ ����� ������������
		}
		else isFound = false;

		if(isFound) continue; 

								
		////////////// �������� ��������� ������ OI //////////////////////////
				
		if( isMatchedTheEndOf( "ns2:BID", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_BID);
		}
		else
		if( isMatchedTheEndOf( "ns2:CommissionNumber", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_CommissionNumber);		
		}
		else
		if( isMatchedTheEndOf( "ns2:CommisionNumberYear", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_CommisionNumberYear);			
		}		
		else
		if( isMatchedTheEndOf( "ns9:ModelYear", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_ModelYear);			
		}		
		else
		if( isMatchedTheEndOf( "ns9:SalesProgram", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_SalesProgram);			
		}		
		else
		if( isMatchedTheEndOf( "ns9:ModelVersion", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_ModelVersion);			
		}		
		else
		if( isMatchedTheEndOf( "ns9:ProductBrand", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_ProductBrand);			
		}		
		else
		if( isMatchedTheEndOf( "ns9:ModelCoding", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_ModelCoding);		
		}
		else
		if( isMatchedTheEndOf( "ns3:SpecialAction", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_SpecialAction);			
		}
		else
		if( isMatchedTheEndOf( "ns3:ProductionNumberYear", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_ProductionNumberYear);			
		}
		else
		if( isMatchedTheEndOf( "ns3:ProductionNumberWeek", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_ProductionNumberWeek);		
		}
		else
		if( isMatchedTheEndOf( "ns3:ProductionNumberDay", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_ProductionNumberDay);			
		}
		else
		if( isMatchedTheEndOf( "ns3:ProductionNumberID", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_ProductionNumberID);			
		}
		else
		if( isMatchedTheEndOf( "ns3:Factory", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_Factory);			
		}
		else
		if( isMatchedTheEndOf( "ns3:VIN", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_VIN);
			
			/* �� VIN ���� 7-8 � 10-17 ������� */
			string s=l_text;

			if( 8 < s.length())
			{
				s=s.substr(5,2)+s.substr(8,8);
			
				copyByLocation( m_bufferOI, s.c_str(), OI_VIN_BODY);
			}
		}
		else
		if( isMatchedTheEndOf( "ns3:EngineNo", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_EngineNo);			
		}
		else
		if( isMatchedTheEndOf( "ns3:EnginePowerIndex", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_EnginePowerIndex);			
		}

		// ������ ��������� PartnerKey
		else
		if( isMatchedTheEndOf( "ns4:Country","ns4:PartnerKey", l_qname, l_step))
		{			
			memcpy((char *)&(l_dealerRef.Country), l_text,4);
		}
		else
		if( isMatchedTheEndOf( "ns4:Brand","ns4:PartnerKey", l_qname, l_step))
		{			
			memcpy((char *)&(l_dealerRef.Brand), l_text,1);
		}
		else
		if( isMatchedTheEndOf( "ns4:PartnerNumber","ns4:PartnerKey", l_qname, l_step))
		{			
			memcpy((char *)&(l_dealerRef.PartnerNumber), l_text,5);
		}
		else
		if( isMatchedTheEndOf( "ns4:PartnerKey","ns3:OrderingDealer", l_qname, l_step))
		{
			std::stringstream ss;

			ss << l_dealerRef.Country << l_dealerRef.Brand<<std::setfill('0')<<std::right << std::setw(5)<<l_dealerRef.PartnerNumber;
			copyByLocation( m_bufferOI, ss.str().c_str(), OI_PartnerKey);			
		}

		//		
		else
		if( isMatchedTheEndOf( "ns3:OrderStatus","ns3:PurchaseOrder", l_qname, l_step))
		{				
			std::stringstream ss;
			
			ss << setfill('0') << std::right << std::setw(4) << l_text;	

			copyByLocation( m_bufferOI, (char *)(ss.str().c_str()), OI_OrderStatus);
		}

		// ������ Colors - �������������� ���������, ���� � ������ ��������� �� ��������� ������ ���� - ����� � ���� �� ������ ������
		else
		if( isMatchedTheEndOf( "ns9:ColourCode","ns9:Finish", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_ColourFinishCode);			
		}
		else
		if( isMatchedTheEndOf( "ns9:ColourCode","ns9:Top", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_ColourTopCode);			
		}
		else
		if( isMatchedTheEndOf( "ns9:InteriorCode","ns9:Interior", l_qname, l_step))
		{
			copyByLocation( m_bufferOI, l_text, OI_InteriorCode);			
		}

		// OI - l_featuresAllvec
		else
		if( isMatchedTheEndOf( "ns9:Features", l_qname, l_step))
		{
			// EG ������ ���������
			std::sort(l_featuresEGvec.begin(), l_featuresEGvec.end(), [](const Feature::Item &p_item1, const Feature::Item &p_item2) -> bool 	
			{
				return (strcmp(p_item1.PRNumber, p_item2.PRNumber) < 0); // ���������� ������ �����������
			});			
			/* ��� �� ������, ���������� ������������ ������ ��� EG �����, ��� L ����� - ��� */

			std::stringstream ss;

			ss = featuresToStringStream(l_featuresEGvec, OI_FeaturesEG.len);

			copyByLocation( m_bufferOI, ss.str().c_str(), OI_FeaturesEG);

			ss = featuresToStringStream(l_featuresLvec, OI_FeaturesL.len);

			copyByLocation( m_bufferOI, ss.str().c_str(), OI_FeaturesL);
			/* ��������� ������ ������ ������������ */			
			/* ��� �� ������, ���������� � ������������ ������ ������ ������������ ������������ ������ ��� EG �����, ��� L ����� - ��� */
			ss = featuresToStringStream(l_featuresEGvec,0);

			setFullComplectForOIFromXml(ss.str());
		
		}
		//
		else
		if( isMatchedTheEndOf( "ns3:IFAOrderType", l_qname, l_step))
		{
			const char *lpArray[] =
			{
				"CUSTOMER_ORDER",
				"IMPORTER_STOCK_ORDER",
				"DEALER_STOCK_ORDER",
				"VOLUNTARY_IMPORTER_STOCK_ORDER",
				nullptr
			};

			for(int i=0;i<4;i++)
			{
				if(!strcmp(lpArray[i],l_text))
				{
					std::stringstream ss;
					
					ss << i;

					copyByLocation( m_bufferOI, ss.str().c_str(), OI_IFAOrderType);	

					break;
				}
			}					
		}
		
		//
		else
		if( isMatchedTheEndOf( "ns3:IFATimingIndicator", l_qname, l_step))
		{
			const char *lpArray[] =
			{
				"ASAP",
				"DESIRED_OR_LATER",
				"DESIRED_OR_EARLIER",
				"CURRENT_WEEK_ONLY",
				nullptr
			};

			for(int i=0;i<4;i++)
			{
				if(!strcmp(lpArray[i],l_text))
				{
					std::stringstream ss;
					
					ss << i;

					copyByLocation( m_bufferOI, ss.str().c_str(), OI_IFATimingIndicator);	

					break;
				}
			}					
		}

		//////  ������ SGW
		else
		if( isMatchedTheEndOf( "ns3:DesiredSGW", l_qname, l_step))
		{
			string s=l_text;

			if(5 < s.length())
			{
				s=s.substr(0,4)+s.substr(5,2);

				copyByLocation( m_bufferOI, s.c_str(), OI_DesiredSGW);			
			}
		}
		
		else
		if( isMatchedTheEndOf( "ns3:ConfirmedSGW", l_qname, l_step))
		{
			string s=l_text;

			if(5 < s.length())
			{
				s=s.substr(0,4)+s.substr(5,2);

				copyByLocation( m_bufferOI, s.c_str(), OI_ConfirmedSGW);			
			}
		}

		//////   ������ CheckPoint
		else
		if( isMatchedTheEndOf( "ns3:TrackingPointNumber", l_qname, l_step))
		{
			memcpy(l_trackingPoint.TrackingPointNumber,l_text,sizeof(l_trackingPoint.TrackingPointNumber));
		}
		else
		if( isMatchedTheEndOf( "ns3:ReachedDate", l_qname, l_step))
		{
			memcpy(l_trackingPoint.ReachedDate,l_text,sizeof(l_trackingPoint.ReachedDate));
		}
		else
		if( isMatchedTheEndOf( "ns3:ReachedTime", l_qname, l_step))
		{
			memcpy(l_trackingPoint.ReachedTime,l_text,sizeof(l_trackingPoint.ReachedTime));
		}
		else
		if( isMatchedTheEndOf( "ns3:PlannedImportedDate", l_qname, l_step))
		{
			memcpy(l_trackingPoint.PlannedImporterDate,l_text,sizeof(l_trackingPoint.PlannedImporterDate));
		}
		else
		if( isMatchedTheEndOf( "ns3:PlannedImportedTime", l_qname, l_step))
		{
			memcpy(l_trackingPoint.PlannedImporterTime,l_text,sizeof(l_trackingPoint.PlannedImporterTime));
		}
		else
		if( isMatchedTheEndOf( "ns3:CurrentETA", l_qname, l_step))
		{
			memcpy(l_trackingPoint.CurrentETA,l_text,sizeof(l_trackingPoint.CurrentETA));
		}
		else
		if( isMatchedTheEndOf( "ns3:PreviousETA", l_qname, l_step))
		{
			memcpy(l_trackingPoint.PreviousETA,l_text,sizeof(l_trackingPoint.PreviousETA));
		}
		else
		if( isMatchedTheEndOf( "ns3:FirstETA", l_qname, l_step))
		{
			memcpy(l_trackingPoint.FirstETA,l_text,sizeof(l_trackingPoint.FirstETA));
		}
		else
		if( isMatchedTheEndOf( "ns3:ETAWarning", l_qname, l_step))
		{
			l_trackingPoint.ETAWarning=("true" == l_text);
		}
		else
		if( isMatchedTheEndOf( "ns3:ContractNumber", l_qname, l_step))
		{
			memcpy(l_trackingPoint.ContractNumber,l_text,sizeof(l_trackingPoint.ContractNumber));
		}
		else
		if( isMatchedTheEndOf( "ns3:ContractPrintedDate", l_qname, l_step))
		{
			memcpy(l_trackingPoint.ContractPrintedDate,l_text,sizeof(l_trackingPoint.ContractPrintedDate));
		}
		else
		if( isMatchedTheEndOf( "ns3:IsCurrentIndicator", l_qname, l_step))
		{
			l_trackingPoint.IsCurrentIndicator=("true" == l_text);
		}
		else
		if( isMatchedTheEndOf( "ns3:ProcessingTimestamp", l_qname, l_step))
		{
			memcpy(l_trackingPoint.ProcessingTimestamp,l_text,sizeof(l_trackingPoint.ProcessingTimestamp));
		}
		else
		if( isMatchedTheEndOf( "ns3:TrackingPoint", l_qname, l_step))
		{			
			l_trackingPointsVec.push_back(l_trackingPoint);
			TrackingPoint::initItem(&l_trackingPoint); // �������� ������������� ��������� ��� ������ ������ ������������
		}
		else		
		if( isMatchedTheEndOf( "ns3:TrackingPoints", l_qname, l_step))
		{			
			auto sortTrackingPointByReachedTimestamp=[](const TrackingPoint::Item &p_item1, const TrackingPoint::Item &p_item2) ->bool
			{	
				if (p_item1.ReachedDate[0] && p_item1.ReachedTime[0] && p_item2.ReachedDate[0] && p_item2.ReachedTime[0])
				{
					int l_res = strcmp(p_item1.ReachedDate, p_item2.ReachedDate);
		
					if (0 != l_res) /* ���� ���� �� �����, ����� ����� �� ���������� */
					{
						return (l_res < 0);
					}
					/* ����� ���������� ������ ��� ��������� ��� */
					return (strcmp(p_item1.ReachedTime, p_item2.ReachedTime) < 0);
				}
				else
				{
					return false;
				}
			};

			std::stringstream ss;				
			bool l_filled = false;
			/* ��������� � ��������������� ������� �� ProcessingTimestamp, ������ Timestamp � ����� */
			std::sort(l_trackingPointsVec.begin(), l_trackingPointsVec.end(), sortTrackingPointByReachedTimestamp);

			const TrackingPoint::Item *lp_lastPoint = nullptr;
			for (auto iter = l_trackingPointsVec.cbegin(); iter != l_trackingPointsVec.cend(); ++iter)
			{
				const TrackingPoint::Item &lItem = *iter;
		
				if ('\0' == lItem.ReachedDate[0] || '\0' == lItem.ReachedTime[0])
				{
					continue;
				}
				/* ���� ��������������� ��� ����� */
				short l_cp = ::getIdByName(coORDER4TrackingPointToCP,lItem.TrackingPointNumber);
				/* ������������� - ���������� ������������, ���� ������ - ������� */		
				if (l_cp < 0 || (lItem.IsCurrentIndicator && l_cp != '8'))
				{
					continue;
				}
				/* ��������� ����� ��� ������, �.�. ������ ������ ������ ����������, ��� ����� ������������� */
				lp_lastPoint = &lItem;
				/* ���� �� ����� '8', �� ��������� */
				if ('8' != l_cp)
				{
					continue;
				}
				// ss << "����� ����� ������� ����� ��� ������ � ���� ������ �������, �������� 0" << "� ����� ������� ���� ��� ������ � ������� yyyymmdd";
		
				std::string l_reacheddate = lItem.ReachedDate;
				ss << static_cast<char>(l_cp) << l_reacheddate.substr(0, 4) << l_reacheddate.substr(5,2) << l_reacheddate.substr(8,2);

				l_filled = true;
				break;
			}
			if (!l_filled && lp_lastPoint)
			{
				short l_cp = ::getIdByName(coORDER4TrackingPointToCP, lp_lastPoint->TrackingPointNumber);

				std::string l_reacheddate = lp_lastPoint->ReachedDate;
				ss << static_cast<char>(l_cp) << l_reacheddate.substr(0, 4) << l_reacheddate.substr(5,2) << l_reacheddate.substr(8,2);

				l_filled = true;
			}
			if( l_filled )
			{
				copyByLocation( m_bufferOI, ss.str().c_str(), OI_TrackingPoints);			
			}
		}		
		// else ��� ���������, ��������� ������ ��� �� ����������� ������, � ��������� �������� ����� � � ��� ����� � � ������
		

		////////////// �������� ��������� ������ IV //////////////////////////
				
		// ��������, ������� ������� ������ ����� ��������, ��� ��� ��� � ��� � ������
		if( isMatchedTheEndOf( "ns9:Features", l_qname, l_step) || 
		    isMatchedTheEndOf( "ns9:Prices"  , l_qname, l_step))
		{
			/* ��������� ������ ����� ������ ���� ���� ������ ���� ����� � ������. ���� ��� ������� ������, �� ������ � ������. */
			if ( 0 < l_featuresAllvec.size()  && 0 < l_pricesVec.size())
			{
				std::stringstream ss;
				for (auto iter = l_pricesVec.cbegin(); iter != l_pricesVec.cend(); ++iter)
				{
					const Price::Item &lItem = *iter;
					/* ��������! ������ ����� ����� ��� PR ���� �� m_featuresTM. �� ��������, ������ ����� ������������ m_featuresTM, � �� l_features.TM (!) */ //  ��������, ��������� l_features.TM �� ����������
					auto iterFeature = std::search_n(l_featuresAllvec.cbegin(), l_featuresAllvec.cend(), 1, lItem.Reference, [](const Feature::Item &lItem, const char *pp_prCode) -> bool
					{
						return (0 == strcmp(pp_prCode, lItem.PRNumber)) && ('L' == lItem.PRType);
					});

					if (iterFeature != l_featuresAllvec.cend())
					{
						ss << std::string(lItem.Reference).substr(0, 3);
						/* ��� ���� ������ L, ��������� ���� �� ���� ������ L ����. �� ����� ���� ������ ��������� ���, �� ������, ���� ����� ������ PRCodesForIV_IsPRCode ���������. */
						auto &lFeatureItem = *iterFeature;
						ss << lFeatureItem.PRType;						
						std::string s=std::to_string(lItem.Amount);
						
						ss << setfill(' ') << std::right << std::setw(13) << std::to_string(lItem.Amount).substr(0, 13).c_str();
					}
				}				
				copyByLocation( m_bufferIV, ss.str().c_str(), IV_Prices);
			}
				
		}
		
		// ��������� ������� ���������
		else
		if( isMatchedTheEndOf( "ns2:BID", l_qname, l_step))
		{
			copyByLocation( m_bufferIV, l_text, IV_BID);			
		}
		else
		if( isMatchedTheEndOf( "ns2:CommissionNumber", l_qname, l_step))
		{
			copyByLocation( m_bufferIV, l_text, IV_CommissionNumber);			
		}
		else
		if( isMatchedTheEndOf( "ns2:CommisionNumberYear", l_qname, l_step))
		{
			copyByLocation( m_bufferIV, l_text, IV_CommisionNumberYear);			
		}	

		// ns3:Price
		else
		if( isMatchedTheEndOf( "ns3:PriceGroup","ns3:Price", l_qname, l_step))
		{  
			memcpy(l_price.PriceGroup,l_text,sizeof(l_price.PriceGroup));
		}
		else
		if( isMatchedTheEndOf( "ns3:PriceType","ns3:Price", l_qname, l_step))
		{
			memcpy(l_price.PriceType,l_text,sizeof(l_price.PriceType));			
		}
		else
		if( isMatchedTheEndOf( "ns3:Reference","ns3:Price", l_qname, l_step))
		{
			memcpy(l_price.Reference,l_text,sizeof(l_price.Reference));			
		}
		else
		if( isMatchedTheEndOf( "ns3:Amount","ns3:Price", l_qname, l_step))
		{
			memcpy(l_price.Currency,l_text,sizeof(l_price.Currency));		

			std::string lText = l_text;
			auto lPos = lText.find_last_of('.');
			if (lPos > 0)
			{
				std::string lMainText = lText.substr(0, lPos);
				std::string lSuffixText = lText.substr(lPos + 1);
				lText = lMainText;
				if (1 == lSuffixText.size())
				{
					lText += '0';
				}
				lText += lSuffixText;
			}

			l_price.Amount = _atoi64(lText.c_str());
		}
		else
		if( isMatchedTheEndOf( "ns3:Price", l_qname, l_step))
		{
			if (0 == strcmp(l_price.PriceGroup, "FACTORYINVOICE"))
			{
				if( 0 == strcmp(l_price.PriceType, "OPTION"))
				{						
					l_pricesVec.push_back(l_price);
				}	
				else
				{
					std::string l_amount;
					
					std::stringstream l_amount_stream;
					l_amount_stream << l_price.Amount;
					l_amount = l_amount_stream.str();	

					std::stringstream ss;
					ss << setfill(' ') << std::right << std::setw(13) << l_amount.substr(0, 13).c_str();					
					
					if (false == l_priceSavedTotal && 0 == strcmp(l_price.PriceType, "VEHICLE_TOTAL")) 
					{
						copyByLocation( m_bufferIV, ss.str().c_str(), IV_PriceTotal);
						l_priceSavedTotal = true;
					}
					else
					if (false == l_priceSavedColor && 0 == strcmp(l_price.PriceType, "COLOR"))
					{					
						copyByLocation( m_bufferIV, ss.str().c_str(), IV_PriceColour);
						l_priceSavedColor = true;
					}
					else	
					if (false == l_priceSavedModel && 0 == strcmp(l_price.PriceType, "MODEL")) 
					{
						copyByLocation( m_bufferIV, ss.str().c_str(), IV_PriceModel);
						l_priceSavedModel = true;
					}
				}
			}		

			Price::initItem(&l_price);	
		}
		// else ��� ���������, ��������� ������ ��� �� ����������� ������, � ��������� �������� ����� � � ��� ����� � � ������


		////////////// �������� ��������� ������ FS //////////////////////////
		
		// ����� �������������  - Features		
		
		if( isMatchedTheEndOf( "ns9:Features", l_qname, l_step))
		{
			std::stringstream ss;

			for (auto iter = l_featuresAllvec.cbegin(); iter != l_featuresAllvec.cend(); ++iter)
			{
				const Feature::Item &lItem = *iter;
				
				if ((ss.str().size() + 4) > BUFFER_FS_SIZE)/* ���� �������� ����� � ������, ��������� ���� ����� */
				{
					break;
				}
				if (ss.str().size())
				{
					ss << ' ';
				}
				ss << lItem.PRNumber << lItem.PRType;
			}			
			copyByLocation( m_bufferFS, ss.str().c_str(), FS_Features);		
				
		}
		else
		if( isMatchedTheEndOf( "ns3:VIN", l_qname, l_step))
		{
			copyByLocation( m_bufferFS, l_text, FS_VIN);			
		}
	}
	
	// ��� �������� ���������, � ����� ������ �� ��������� - ������ �� ����� ����, �� �� ��������������
	m_errorString = "����������� ����� XML";
	m_isValid = false;
	
	m_orderNum=-1;
	mp_parser->parseReset(*mp_scanToken);

	return false;
}
#pragma once

#if !defined(__ORDERXml_HPP)
#define __ORDERXml_HPP

#include "CODLLdef.h"
#include <string>	
#include <xercesc/sax2/SAX2XMLReader.hpp>

#include "ORDERXmlTypes.hpp"

////////////////////////////////////////////////////
/// ��������� ������-�������
////////////////////////////////////////////////////
class XMLContentHandler;

// �������������� ����� ������ � �������, ������������������ ������� (����������) �������
typedef struct
{
	int offset;
	int len;
}OFFLEN;

class CO_EXPORT ORDERXml
{
private:
	enum BUF_SIZES
	{
	  BUFFER_OI_SIZE = 2500,
	  BUFFER_IV_SIZE = 5000,
	  BUFFER_FS_SIZE = 1800
	};

	public:
	ORDERXml( const char *ppFileName );
	virtual ~ORDERXml();
		
	static ORDERXml *CreateORDERXml( const char *xmlFile );
	
	bool			isValid()			const	{ return m_isValid; }
	bool			hasError()			const	{ return ( m_errorString.size() > 0 ); } 
	std::string		getErrorString()	const	{ return m_errorString; }

	bool			parseFile();
	
	bool			getLine( IDataAggregationRecordType pType, std::string &pBuffer ); //���������� ������ ���� pType �� �������������� ����������� ������� ������
	
	bool			goToNextOrder(); // ��������� � ���������� ������ � ��������� ������ ������

	int				getOrderNum()		const { return m_orderNum; } // ����� ������ � �����
private:
	
	std::string		formXsdFileName(const std::string &p_xsdFilePath, const char *pp_newFileName); // ��������� ������ ��� (� �.�. ����) ��� ��������� xsd �����. 
			
	bool						m_isValid;
	const std::string			m_fileName;
	std::string					m_errorString;
		
	char	m_bufferOI [ BUFFER_OI_SIZE ];
	char	m_bufferIV [ BUFFER_IV_SIZE ];
	char	m_bufferFS [ BUFFER_FS_SIZE ];	

	xercesc::SAX2XMLReader		*mp_parser;    // ������������ ������
	xercesc::XMLPScanToken		*mp_scanToken; // ����� ��� ������ ���������� ��������
	XMLContentHandler			*mp_handler;   // ���������� ������� (����� �������� � ������)

	long						m_orderNum; // ������� ������� (-1 - �� ������ ��� ���������)

	// ���������� ������� �������
	bool	startParseSyncOrder();	// ��������� ��������� �������
	bool	gotoNextSyncOrder();	// ���� ������ ������
	bool	fillBuffers();			// ���������� ������� � ���������� ���� ������ ��� ������ ������
	bool	validate(const char *xmlFile,const char *xsdFile=nullptr,const char *extLink=nullptr); // �������� �����, �������� � ���������� � �������
	// ������� �������� ������������ ������� ������������ ���� xml-����� (qname) �������
	inline bool isMatchedTheStartOf( const char *sampleTag, const char *qname, int step);
	inline bool isMatchedTheEndOf( const char *sampleTag, const char *qname, int step);
	inline bool isMatchedTheEndOf( const char *sampleTag, const char *sampleParentTag, const char *qname, int step); // ����� ����������� ������� ������� ����� ������������ �����

	inline void copyByLocation(char *p_buffer, const char *p_text, const OFFLEN &l_location);  // ���������� ������ � ������������ � location

	/*
	* ��������� ��� Xml ������ ������������ ����� ���� ������, ��� ����������� 60 PR �����. ������ ��� ������������ ��������.
	*          ������ �������� �������� ������������ (� ���������� ����) � ������� �����, � ����� �� ������� ������ ������������ ��� �����������.
	*/
private:
	std::string			m_fullComplectForOIFromXml;
	void setFullComplectForOIFromXml(std::string s)
	{
		m_fullComplectForOIFromXml = s;
	}
public:
	std::string getFullComplectForOIFromXml() const
	{
		return m_fullComplectForOIFromXml;
	}
};


#endif

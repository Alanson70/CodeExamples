#pragma once

#if !defined(__ORDERXml_HPP)
#define __ORDERXml_HPP

#include "CODLLdef.h"
#include <string>	
#include <xercesc/sax2/SAX2XMLReader.hpp>

#include "ORDERXmlTypes.hpp"

////////////////////////////////////////////////////
/// Разборщик файлов-заказов
////////////////////////////////////////////////////
class XMLContentHandler;

// местоположение полей заказа в буферах, соответветствующих старому (текстовому) формату
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
	
	bool			getLine( IDataAggregationRecordType pType, std::string &pBuffer ); //возвращает данные типа pType из предварительно заполненных буферов данных
	
	bool			goToNextOrder(); // переходит к следующеей записи и заполняет буфера данных

	int				getOrderNum()		const { return m_orderNum; } // номер заказа в файле
private:
	
	std::string		formXsdFileName(const std::string &p_xsdFilePath, const char *pp_newFileName); // Формируем полное имя (в т.ч. путь) для корневого xsd файла. 
			
	bool						m_isValid;
	const std::string			m_fileName;
	std::string					m_errorString;
		
	char	m_bufferOI [ BUFFER_OI_SIZE ];
	char	m_bufferIV [ BUFFER_IV_SIZE ];
	char	m_bufferFS [ BUFFER_FS_SIZE ];	

	xercesc::SAX2XMLReader		*mp_parser;    // библиотечный парсер
	xercesc::XMLPScanToken		*mp_scanToken; // нужно для работы пошагового парсинга
	XMLContentHandler			*mp_handler;   // обработчик событий (шагов парсинга и ошибок)

	long						m_orderNum; // счетчик заказов (-1 - не начали или закончили)

	// внутренние функции парсера
	bool	startParseSyncOrder();	// Запускает пошаговый парсинг
	bool	gotoNextSyncOrder();	// Ищет начало заказа
	bool	fillBuffers();			// Подготовка буферов и заполнение всех данных для одного заказа
	bool	validate(const char *xmlFile,const char *xsdFile=nullptr,const char *extLink=nullptr); // открытие файла, проверка и подготовка к разбору
	// функции проверки соответствия полного наименования тэга xml-файла (qname) образцу
	inline bool isMatchedTheStartOf( const char *sampleTag, const char *qname, int step);
	inline bool isMatchedTheEndOf( const char *sampleTag, const char *qname, int step);
	inline bool isMatchedTheEndOf( const char *sampleTag, const char *sampleParentTag, const char *qname, int step); // также проверяется наличие образца среди родительских тэгов

	inline void copyByLocation(char *p_buffer, const char *p_text, const OFFLEN &l_location);  // размещение данных в соответствии с location

	/*
	* Поскольку для Xml файлов комплектация может быть больше, чем стандартные 60 PR кодов. Храним эту комплектацию отдельно.
	*          Старый алгоритм поместит комплектацию (в обрезанном виде) в обучное место, а здесь мы получим полную комплектацию без ограничений.
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

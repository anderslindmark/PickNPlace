#ifndef __SETTINGS_H__
#define __SETTINGS_H__

enum XmlInDataType {XMLDATA_INT};

#include <QXmlSimpleReader>
#include "MachineController.h"
namespace PicknPlaceGui
{
	class Settings : public QXmlDefaultHandler
	{
	public:
		Settings(QString file);
		~Settings(void);
		bool Read();
		PickStateStruct GetPNPSettings();
		void SetPNPSettings(PickStateStruct pnp);
		DispenceStateStruct GetDispenceSettings();
		void SetDispenceSettings(DispenceStateStruct dis);
		void SetFile(QString file);
		bool Save();

		//Content handle functions:
		bool characters ( const QString & ch );
		bool startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts );
		bool endElement ( const QString & namespaceURI, const QString & localName, const QString & qName );


	private:
		QString m_file;
		QXmlSimpleReader *m_xmlReader;
		PickStateStruct m_pickSettings;
		DispenceStateStruct m_dispenceSettings;
		int *m_intEntry;
		XmlInDataType m_type;
		bool m_skip;



	};
}
#endif // __SETTINGS_H__
#include "Settings.h"
#include <qdom.h>
#include <QFile>
#include <iostream>
using namespace std;
namespace PicknPlaceGui
{
	Settings::Settings(QString file) : m_file(file)
	{
		m_intEntry = NULL;
		m_skip = false;
	}

	Settings::~Settings(void)
	{
	}

	bool Settings::Read()
	{
		bool returnVal;
		QFile file(m_file);
		QXmlInputSource src(&file);
		QXmlSimpleReader xmlReader;
		xmlReader.setFeature( "http://xml.org/sax/features/namespaces",
                           true );
		xmlReader.setFeature( "http://xml.org/sax/features/namespace-prefixes",
                           true );
		xmlReader.setContentHandler(this);
		xmlReader.setErrorHandler(this);
		returnVal = xmlReader.parse(&src);

		return returnVal;
	}

	PickStateStruct Settings::GetPNPSettings()
	{
		return m_pickSettings;
	}
	void Settings::SetPNPSettings(PickStateStruct pnp)
	{
		m_pickSettings = pnp;
	}
		
	DispenceStateStruct Settings::GetDispenceSettings()
	{
		return m_dispenceSettings;
	}

	void Settings::SetDispenceSettings(DispenceStateStruct dis)
	{
		m_dispenceSettings = dis;
	}

	void Settings::SetFile(QString file)
	{
		m_file = file;
	}
	bool Settings::Save()
	{
		QString value;
		QDomDocument doc;
		// create root
		QDomElement root = doc.createElement( "settings" );
		doc.appendChild( root );

		QDomElement mc = doc.createElement( "machinecontroller" );
		root.appendChild(mc);

		// create pickandplace
		QDomElement pnp = doc.createElement("pnp:pickandplace");
		mc.appendChild( pnp );
			QDomElement e = doc.createElement("pnp:offsetX");
				pnp.appendChild(e);
				QDomText t = doc.createTextNode(QString::number(m_pickSettings.offsetX));
				e.appendChild( t );
			e = doc.createElement("pnp:offsetY");
				pnp.appendChild(e);
				t = doc.createTextNode(QString::number(m_pickSettings.offsetY));
				e.appendChild( t );
			e = doc.createElement("pnp:headHeight");
				pnp.appendChild(e);
				t = doc.createTextNode(QString::number(m_pickSettings.headHeight));
				e.appendChild( t );
			e = doc.createElement("pnp:pickHeight");
				pnp.appendChild(e);
				t = doc.createTextNode(QString::number(m_pickSettings.pickHeight));
				e.appendChild( t );
			e = doc.createElement("pnp:placeHeight");
				pnp.appendChild(e);
				t = doc.createTextNode(QString::number(m_pickSettings.placeHeight));
				e.appendChild( t );
			e = doc.createElement("pnp:afterPickTime");
				pnp.appendChild(e);
				t = doc.createTextNode(QString::number(m_pickSettings.afterPickTime));
				e.appendChild( t );
			e = doc.createElement("pnp:pickPressDownTime");
				pnp.appendChild(e);
				t = doc.createTextNode(QString::number(m_pickSettings.pickPressDownTime));
				e.appendChild( t );
			e = doc.createElement("pnp:placePressDownTime");
				pnp.appendChild(e);
				t = doc.createTextNode(QString::number(m_pickSettings.placePressDownTime));
				e.appendChild( t );
			e = doc.createElement("pnp:afterPlaceTime");
				pnp.appendChild(e);
				t = doc.createTextNode(QString::number(m_pickSettings.afterPlaceTime));
				e.appendChild( t );

		// create dispence settings
		QDomElement dis = doc.createElement("d:dispence");
		mc.appendChild( dis );
			e = doc.createElement("d:offsetX");
				dis.appendChild(e);
				t = doc.createTextNode(QString::number(m_dispenceSettings.offsetY));
				e.appendChild( t );
			e = doc.createElement("d:offsetY");
				dis.appendChild(e);
				t = doc.createTextNode(QString::number(m_dispenceSettings.offsetX));
				e.appendChild( t );
			e = doc.createElement("d:offsetZ");
				dis.appendChild(e);
				t = doc.createTextNode(QString::number(m_dispenceSettings.offsetZ));
				e.appendChild( t );
			e = doc.createElement("d:offsetZs");
				dis.appendChild(e);
				t = doc.createTextNode(QString::number(m_dispenceSettings.offsetZs));
				e.appendChild( t );
			e = doc.createElement("d:offsetTurn");
				dis.appendChild(e);
				t = doc.createTextNode(QString::number(m_dispenceSettings.offsetTurn));
				e.appendChild( t );
			e = doc.createElement("d:speed");
				dis.appendChild(e);
				t = doc.createTextNode(QString::number(m_dispenceSettings.speed));
				e.appendChild( t );
			e = doc.createElement("d:beforeTime");
				dis.appendChild(e);
				t = doc.createTextNode(QString::number(m_dispenceSettings.beforeTime));
				e.appendChild( t );
			e = doc.createElement("d:afterTime");
				dis.appendChild(e);
				t = doc.createTextNode(QString::number(m_dispenceSettings.afterTime));
				e.appendChild( t );
			e = doc.createElement("d:suckBackTime");
				dis.appendChild(e);
				t = doc.createTextNode(QString::number(m_dispenceSettings.suckBackTime));
				e.appendChild( t );

		// save information to file
		QString xml = doc.toString();
		QFile file(m_file);
		file.open(QIODevice::WriteOnly);
		file.write(xml.toStdString().c_str(), xml.length());
		file.close();
		return true;
	}

	//READER FUNCTIONS
	bool Settings::characters ( const QString & ch )
	{
		bool ok = true;
		if (!m_skip)
		{
			ok = false;
			switch (m_type) {
				case XMLDATA_INT: *m_intEntry = ch.toInt(&ok);
					break;
				default:
					break;
			}
			m_skip = true;
		}
		if (!ok)
		{
			this->error(QXmlParseException(QString("Error when parsing an value!")));
			return false;
		}
		//cout << "IN CHARACTERS" << endl;
		//cout << ch.toStdString() << endl;
		return true;
	}

	bool Settings::startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts )
	{
		m_skip = false;

		//PICK AND PLACE SETTINGS
		if (qName == "pnp:offsetX")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_pickSettings.offsetX;
		} 
		else if (qName == "pnp:offsetY")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_pickSettings.offsetY;
		}
		else if (qName == "pnp:headHeight")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_pickSettings.headHeight;
		}
		else if (qName == "pnp:pickHeight")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_pickSettings.pickHeight;
		}
		else if (qName == "pnp:placeHeight")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_pickSettings.placeHeight;
		}
		else if (qName == "pnp:afterPickTime")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_pickSettings.afterPickTime;
		}
		else if (qName == "pnp:pickPressDownTime")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_pickSettings.pickPressDownTime;
		}
		else if (qName == "pnp:placePressDownTime")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_pickSettings.placePressDownTime;
		}
		else if (qName == "pnp:afterPlaceTime")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_pickSettings.afterPlaceTime;
		} 
		// DISPENCE SETTINGS
		else if (qName == "d:offsetX")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_dispenceSettings.offsetX;
		}
		else if (qName == "d:offsetY")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_dispenceSettings.offsetY;
		}
		else if (qName == "d:offsetZ")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_dispenceSettings.offsetZ;
		}
		else if (qName == "d:offsetZs")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_dispenceSettings.offsetZs;
		}
		else if (qName == "d:offsetTurn")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_dispenceSettings.offsetTurn;
		}
		else if (qName == "d:speed")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_dispenceSettings.speed;
		}
		else if (qName == "d:beforeTime")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_dispenceSettings.beforeTime;
		}
		else if (qName == "d:afterTime")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_dispenceSettings.afterTime;
		}
		else if (qName == "d:suckBackTime")
		{
			m_type = XMLDATA_INT;
			m_intEntry = &m_dispenceSettings.suckBackTime;
		}
		else 
		{
			m_skip = true;
		}

		//cout << "IN startElement" << endl;
		//cout << "NAMESPACE : \"" << namespaceURI.toStdString() <<"\""<< endl;
		//cout << "LOCALNAME : " << localName.toStdString() << endl;
		//cout << "QNAME : \"" << qName.toStdString() << "\""<<endl;
		//cout << "QXMLATTRIBUTES : " << atts.count() << endl;
		return true;
	}

	bool Settings::endElement ( const QString & namespaceURI, const QString & localName, const QString & qName )
	{
		//cout << "IN endElement" << endl;
		
		return true;
	}
}
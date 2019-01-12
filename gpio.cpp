#include "gpio.h"


GPIO::GPIO(const unsigned int &pinNumber) : pinNumber(pinNumber){
    exportGPIO();
}

GPIO::~GPIO(){
    unexportGPIO();
}

bool GPIO::exportGPIO(void){
    return writeToGPIOFile( baseGPIOPath_ + gpioExport_, QString::number(pinNumber) );
}

bool GPIO::unexportGPIO(void)
{
  return writeToGPIOFile( baseGPIOPath_ + gpioUnexport_, QString::number(pinNumber) );
}

bool GPIO::writeToGPIOFile( const QString file, const QString outputData )
{
  QFile exportFile( file );

  if ( exportFile.open( QIODevice::WriteOnly ) )
  {
    QTextStream exportStream( &exportFile );

    exportStream << outputData;

    exportFile.close();

    return true;
   }

  qDebug() << "Error writing " << file;

  return false;
}

bool GPIO::readFromGPIOFile( const QString file, QString &inputData )
{
  QFile inputFile( file );

  if ( inputFile.open( QIODevice::ReadOnly ) )
  {
    QTextStream inputStream( &inputFile );

    inputStream >> inputData;

    inputFile.close();

    return true;
   }

  qDebug() << "Error reading " << file;

  return false;
}

bool GPIO::setDirection( const GPIODirection &read )
{
  bool result = false;
  QString path = baseGPIOPath_ + "gpio" + QString::number(pinNumber) + "/" + gpioDirection_;

  if ( read == GPIO::Read )
    result = writeToGPIOFile( path, "in" );
  else
    result = writeToGPIOFile( path, "out" );

  return result;
}

bool GPIO::setValue( const GPIOState &value )
{
  bool result = false;
  QString path = baseGPIOPath_ + "gpio" + QString::number(pinNumber) + "/" + gpioValue_;

  if ( value == GPIOState::Down )
    result = writeToGPIOFile( path, "1" );
  else
    result = writeToGPIOFile( path, "0" );

  return result;
}

bool GPIO::getValue(GPIOState &value )
{
  bool result = false;
  QString data = "";
  QString path = baseGPIOPath_ + "gpio" + QString::number(pinNumber) + "/" + gpioValue_;

  result = readFromGPIOFile( path, data );

  if ( result )
    value=(data == "1")?Up:Down;

  return result;
}

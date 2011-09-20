#include "Environment.h"

#include <stdlib.h>

#include "iException.h"
#include "iString.h"
#include "TextFile.h"


namespace Isis {

  /**
   * @Returns the user name. Returns 'Unknown' if it cannot find the user name.
   */
  iString Environment::userName() {
    return getEnvironmentValue("USER", "Unknown");
  }
  

  /**
   * @returns the host name.  Returns 'Unknown' if it cannot find the host name.
   */
  iString Environment::hostName() {
    return getEnvironmentValue("HOST", "Unknown");
  }
  
  
  /**
   * @param variable The environment variable to get
   * @param defaultValue The returned value for variable if variable doesn't
   *                     exist.
   *
   * @returns The value for the environment variable requested.
   */
  iString Environment::getEnvironmentValue(iString variable,
      iString defaultValue) {
      
    iString value = defaultValue;
    
    char *envValue = getenv(variable.c_str());
    if (envValue)
      value = envValue;
      
    return value;
  }
  

  /**
   * @returns the Isis version in the format isis?.?.?.?qualifier | date
   */
  iString Environment::isisVersion() {
    TextFile versionFile("$ISISROOT/version");
    iString line1, line2, line3, line4;
    versionFile.GetLine(line1);
    versionFile.GetLine(line2);
    versionFile.GetLine(line3);
    versionFile.GetLine(line4);

    QRegExp validPartOfLine("[^ #]*");
    if (validPartOfLine.indexIn(line1) != -1) {
      line1 = validPartOfLine.cap();
    }
    else {
      iString msg = "$ISISROOT/version line 1, no valid text found";
      throw iException::Message(iException::Programmer, msg, _FILEINFO_);
    }

    if (validPartOfLine.indexIn(line2) != -1) {
      line2 = validPartOfLine.cap();
    }
    else {
      iString msg = "$ISISROOT/version line 2, no valid text found";
      throw iException::Message(iException::Programmer, msg, _FILEINFO_);
    }

    if (validPartOfLine.indexIn(line4) != -1) {
      line4 = validPartOfLine.cap();
    }
    else {
      iString msg = "$ISISROOT/version line 4, no valid text found";
      throw iException::Message(iException::Programmer, msg, _FILEINFO_);
    }

    return line1 + " " + line4 + " | " + line2;
  }
}

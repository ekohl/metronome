#pragma once
#include <string>
#include <stdexcept>
#include <errno.h>
#include <string.h>
#include <vector>
using std::string;

inline void unixDie(const string &why)
{
  throw std::runtime_error(why+": "+strerror(errno));
}

template <typename Container>
void
stringtok (Container &container, string const &in,
           const char * const delimiters = " \t\n")
{
  const string::size_type len = in.length();
  string::size_type i = 0;
  
  while (i<len) {
    // eat leading whitespace
    i = in.find_first_not_of (delimiters, i);
    if (i == string::npos)
      return;   // nothing left but white space
    
    // find the end of the token
    string::size_type j = in.find_first_of (delimiters, i);
    
    // push token
    if (j == string::npos) {
      container.push_back (in.substr(i));
      return;
    } else
      container.push_back (in.substr(i, j-i));
    
    // set up for next loop
    i = j + 1;
  }
}

#define infolog(X,Y) if(g_verbose) { syslog(LOG_INFO, "%s", (boost::format((X)) % Y).str().c_str()); \
    if(g_console) cout << boost::format((X)) %Y << endl; } do{}while(0)
#define warnlog(X,Y) { syslog(LOG_WARNING, "%s", (boost::format((X)) % Y).str().c_str()); \
    if(g_console) cout << boost::format((X)) %Y << endl; } do{}while(0)
#define errlog(X,Y) {syslog(LOG_ERR, "%s", (boost::format((X)) % Y).str().c_str()); \
    if(g_console) cout << boost::format((X)) %Y << endl; }do{}while(0)

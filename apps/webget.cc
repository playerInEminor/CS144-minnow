#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  TCPSocket socket;

  socket.connect(Address(host, "http"));

  /*
    GET {path} HTTP/1.1
    Host: {host}
    Connection: close
  */

  string get_cmd = "GET " + path + " HTTP/1.1\r\n";
  string host_cmd = "Host: " + host + "\r\n";
  string close_cmd = "Connection: close\r\n";
  string final_cmd = "\r\n";
  string cmd = get_cmd + host_cmd + close_cmd + final_cmd;

  if(socket.write(cmd) == cmd.length()){
    while (cmd != "")
    {
      socket.read(cmd);
      cout << cmd;
    }
  }
  else{
    cout << "Send failed" << endl;
  }
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

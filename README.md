# webserver

Simple web-server, which is able to serve a fully static website.

It works according to configuration file, where you can:

• Choose the port and host of each ’server’.

• Setup the server_names or not.

• The first server for a host:port will be the default for this host:port (that means
it will answer to all the requests that don’t belong to an other server).

• Setup default error pages.

• Limit client body size.

• Setup routes with one or multiple of the following rules/configuration (routes wont
be using regexp):

◦ Define a list of accepted HTTP methods for the route.

◦ Define a HTTP redirection.

◦ Define a directory or a file from where the file should be searched (for example,
if url /kapouet is rooted to /tmp/www, url /kapouet/pouic/toto/pouet is
/tmp/www/pouic/toto/pouet).

◦ Turn on or off directory listing.

Webserver supports GET, POST, PUT, DELETE and HEAD methods.

The project is buildшng with Makefile, and executing with a name of configuration file argument 

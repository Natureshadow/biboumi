Version 2.0 - 2015-05-29
========================

 - List channels on an IRC server through an XMPP disco items request
 - Let the user send any arbitrary raw IRC command by sending a
   message to the IRC server’s JID.
 - By default, look for the configuration file as per the XDG
   basedir spec.
 - Support PING requests in all directions.
 - Improve the way we forward received NOTICEs by remembering to
   which users we previously sent a private message.  This improves the
   user experience when talking to NickServ.
 - Support joining key-protected channels
 - Setting a participant's role/affiliation now results in a change of IRC
   mode, instead of being ignored.  Setting Toto's affiliation to admin is
   now equivalent to “/mode +o Toto”
 - Fix the reconnection to the XMPP server to try every 2 seconds
   instead of immediately. This avoid hogging resources for nothing
 - Asynchronously resolve domain names by optionally using the DNS
   library c-ares.
 - Add a reload add-hoc command, to reload biboumi's configuration
 - Add a fixed_irc_server option.  With this option enabled,
   biboumi can only connect to the one single IRC server configured

Version 1.1 - 2014-07-16
========================

 - Fix a segmentation fault when connecting to an IRC server using IPv6

Version 1.0 - 2014-07-12
========================

 - First stable release.
 - Mostly complete MUC to IRC, and IRC to MUC support
 - Complete handling of private messages
 - Full IRC modes support: setting any IRC mode, and receiving notifications
   for every mode change
 - Verbose connection status notifications
 - Conversion from IRC formatting to XHTML-im
 - Ad-hoc commands support
 - Basic TLS support: auto-accepts all certificates, no cipher
   configuration, no way to force usage of TLS (it is used only if
   available, clear connection is automatically used as a fallback)
 - IPv6 support

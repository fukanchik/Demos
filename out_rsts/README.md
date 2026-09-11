See spike of OutRsts on unclosed socket when program crashes. Such a spike in
your monitoring system can be a good indicator of a server crash.

RFC 2525 Section 2.17 "Known TCP Implementation Problems"
"Failure to RST on close with data pending".

RFC 1122 Section 4.2.2.13 "Closing a Connection"
"(2) an "abort" in which one or more RST segments are sent and the connection
state is immediately discarded.

If such a host issues a CLOSE call while received data is still pending in TCP,
or if new data is received after CLOSE is called, its TCP SHOULD send a RST to
show that data was lost.

RFC-793 Section 3.5 "Closing a Connection"
Says nothing

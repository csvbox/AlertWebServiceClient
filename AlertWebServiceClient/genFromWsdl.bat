wsdl2h -o AlertWebService.h AlertWebService.wsdl
soapcpp2 -j -CL -I.\import AlertWebService.h

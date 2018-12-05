wsdl2h -o AlertWebService.h AlertWebService.wsdl
soapcpp2 -j -CL -I.\import AlertWebService.h

wsdl2h -o EproService.h ProvisionService.wsdl AlertWebService.wsdl
soapcpp2 -e -C -pepro -I.\import -L -1 -x -w -i EproService.h

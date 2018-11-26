#include <iostream>
#include "AlertWebServiceSoapBinding.nsmap"
#include "soapAlertWebServiceSoapBindingProxy.h"

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("usage: %s <IPv4 address or FQDN> <port>\n", argv[0]);
        printf("example usage:\n");
        printf("\t%s 127.0.0.1 8443\n", argv[0]);
        return 1;
    }

    std::string endpoint{ argv[1] };
    endpoint.append(":").append(argv[2]);

    std::string centerCordIPAddress;
    int centerCordAODFeedPortNum = 0;
    int centerCordCSLPortNum = 0;
    int answer = 0;

    std::cout << "Testing AlertWebService endpoint: " << endpoint << "\n";
    AlertWebServiceSoapBindingProxy alertProxy(0, 0);
    alertProxy.soap_endpoint = endpoint.c_str();
    ns1__GetRunningCenterCordResponse eproResponse;

    try
    {
        answer = alertProxy.GetRunningCenterCord(eproResponse);
    }
    catch (const std::exception&)
    {
        std::cout << "Exception calling AlertWebService endpoint\n";
    }

    std::cout << "Answer:" << answer;
    if (answer == 0)
    {
        std::string strCCIPAddr = *eproResponse.GetRunningCenterCordReturn->IPAddress;
        std::cout << "CenterCordInfo:(" << strCCIPAddr
            << "), AODFeedPort:(" << eproResponse.GetRunningCenterCordReturn->AODFeedPortNum
            << "), CSL Port:(" << eproResponse.GetRunningCenterCordReturn->CSLPortNum << ")";

        if (eproResponse.GetRunningCenterCordReturn->IPAddress)
        {
            centerCordIPAddress = *eproResponse.GetRunningCenterCordReturn->IPAddress;
        }
        if (eproResponse.GetRunningCenterCordReturn->AODFeedPortNum)
        {
            centerCordAODFeedPortNum = eproResponse.GetRunningCenterCordReturn->AODFeedPortNum;
        }
        if (eproResponse.GetRunningCenterCordReturn->CSLPortNum)
        {
            centerCordCSLPortNum = eproResponse.GetRunningCenterCordReturn->CSLPortNum;
        }
        if (0 == centerCordIPAddress.length() || 0 == centerCordCSLPortNum || 0 == centerCordAODFeedPortNum)
        {
            std::cout << "Not valid IP Address or AODFeed port number from CenterCord for Dialer\n";
        }
    }
    else
    {
        std::cout << " received " << answer << " while connecting to AlertWebService.";
        alertProxy.soap_stream_fault(std::cout);
    }

    alertProxy.destroy();

    return 0;
}
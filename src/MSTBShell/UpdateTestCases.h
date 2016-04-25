// UpdateTestCases.h: interface for the UpdateTestCases class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPDATETESTCASES_H__EC839565_58A5_4B2F_A2DA_2FC5725BD9C7__INCLUDED_)
#define AFX_UPDATETESTCASES_H__EC839565_58A5_4B2F_A2DA_2FC5725BD9C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TestSuite.h"



class UpdateTestCases : public TestSuite  
{
private:
	static int test_update_manager(int argc,char*argv[]);
	static int test_set_home(int argc,char*argv[]);
	static int test_upgrade(int argc,char*argv[]);
	static int test_update_item(int argc,char*argv[]);
	int static  test_gen_cases(int argc,char *argv[]);
	int static  test_basic(int argc,char *argv[]);
	int  static  split_file(int argc, char* argv[]);
	int  static tcp_client_connect(int argc, char* argv[]);
	int  static tcp_client_send(int argc, char* argv[]);
	int  static tcp_client_recv(int argc, char* argv[]);
	int  static tcp_client_recv_timeout(int argc, char* argv[]);
	int  static tcp_client_unkown_host(int argc, char* argv[]);
	int  static tcp_client_read(int argc, char* argv[]);
	int  static tcp_client_download_file(int argc, char* argv[]);
	int  static url_basic(int argc, char* argv[]);
	int  static url_eval(int argc, char* argv[]);
	int  static tcp_url_download(int argc, char* argv[]);
	int  static http_header(int argc, char* argv[]);
	int  static http_resource_size(int argc, char* argv[]);
	int  static web_time(int argc, char* argv[]);
	int  static http_is_update(int argc, char* argv[]);
	int  static http_update(int argc, char* argv[]);	
	int  static http_no_update(int argc, char* argv[]);	
	int  static doc_client(int argc, char* argv[]);	
	int  static doc_file_size(int argc, char* argv[]);
	int  static doc_send_file(int argc, char* argv[]);
public:
	void registerTestCases();
	static int refresh_desktop(int argc,char**argv);

	int run(int agrc, char ** argv);


	UpdateTestCases();
	virtual ~UpdateTestCases();

};

#endif // !defined(AFX_UPDATETESTCASES_H__EC839565_58A5_4B2F_A2DA_2FC5725BD9C7__INCLUDED_)

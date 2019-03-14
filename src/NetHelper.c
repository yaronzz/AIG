//#include "uv.h"
//#include "NetHelper.h"
//
//#pragma comment(lib, "..\\lib\\libuv\\libuv.lib")
//
//
//void on_new_connection(uv_stream_t *server, int status) {
//	if (status == -1) {
//		// error!
//		return;
//	}
//
//	//uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
//	//uv_tcp_init(loop, client);
//	//if (uv_accept(server, (uv_stream_t*)client) == 0) {
//	//	uv_read_start((uv_stream_t*)client, alloc_buffer, echo_read);
//	//}
//	//else {
//	//	uv_close((uv_handle_t*)client, NULL);
//	//}
//}
//
//int net_StartTcpServer() 
//{
//	int iCheck;
//	uv_loop_t* pLoop;
//	uv_tcp_t aServerStream;
//	struct sockaddr_in aServerAddress;
//
//	pLoop  = uv_default_loop();
//	iCheck = uv_tcp_init(pLoop, &aServerStream);
//	if (iCheck < 0)
//		return eAEC_InitErr;
//
//	iCheck = uv_ip4_addr("0.0.0.0", 7000, &aServerAddress);
//	if (iCheck < 0)
//		return eAEC_CoverAddr;
//
//	iCheck = uv_tcp_bind(&aServerStream, (const struct sockaddr*)&aServerAddress, 0);
//	if (iCheck < 0)
//		return eAEC_BindErr;
//
//	iCheck = uv_listen((uv_stream_t*)&aServerStream, 128, on_new_connection);
//	if (iCheck < 0)
//		return eAEC_ListenErr;
//
//	uv_run(pLoop, UV_RUN_DEFAULT);
//	return uv_loop_close(pLoop);
//}
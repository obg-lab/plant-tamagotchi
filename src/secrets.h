#include <pgmspace.h>

#define SECRET

const char ssid[] = "SUA REDE WIFI";
const char pass[] = "SUA SENHA WIFI";

#define THINGNAME "69e0f7b2-0dd7-4c11-bf72-14babb57a9eb"

int8_t TIME_ZONE = -3;
//#define USE_SUMMER_TIME_DST  // descomente se voce estiver em horario de verãonce

const char MQTT_HOST[] = "eugenioprod-iothub.azure-devices.net";
const char MQTT_USER[] = "eugenioprod-iothub.azure-devices.net/" THINGNAME "/api-version=2017-06-30";
const int MQTT_PORT = 8883;
const char MQTT_SUB_TOPIC[] = "$iothub/methods/POST/#";
const char MQTT_PUB_TOPIC[] = "devices/" THINGNAME "/messages/events/";


// Copie aqui o seu certificado CA do EUGENIO (ex: CAxxxxx.pem) ▼
static const char cacert[] PROGMEM = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJ\n" \
"RTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYD\n" \
"VQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoX\n" \
"DTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMCSUUxEjAQBgNVBAoTCUJhbHRpbW9y\n" \
"ZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFsdGltb3JlIEN5YmVy\n" \
"VHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKMEuyKr\n" \
"mD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjr\n" \
"IZ3AQSsBUnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeK\n" \
"mpYcqWe4PwzV9/lSEy/CG9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSu\n" \
"XmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9XbIGevOF6uvUA65ehD5f/xXtabz5OTZy\n" \
"dc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjprl3RjM71oGDHweI12v/ye\n" \
"jl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoIVDaGezq1\n" \
"BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3\n" \
"DQEBBQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT92\n" \
"9hkTI7gQCvlYpNRhcL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3Wgx\n" \
"jkzSswF07r51XgdIGn9w/xZchMB5hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0\n" \
"Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsaY71k5h+3zvDyny67G7fyUIhz\n" \
"ksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9HRCwBXbsdtTLS\n" \
"R9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp\n" \
"-----END CERTIFICATE-----\n";


// Copie aqui o seu certificar do cliente do EUGENIO (ex: xxxxx.pem) ▼
static const char client_cert[] PROGMEM = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDCTCCAfGgAwIBAgIUR6Km7gP02S7o89HbAgSte+lzY1QwDQYJKoZIhvcNAQEL\n" \
"BQAwFDESMBAGA1UEAwwJbG9jYWxob3N0MB4XDTIwMTEwODIyNDgzOFoXDTIxMTEw\n" \
"ODIyNDgzOFowFDESMBAGA1UEAwwJbG9jYWxob3N0MIIBIjANBgkqhkiG9w0BAQEF\n" \
"AAOCAQ8AMIIBCgKCAQEApo/C8JlqyBwutYiFKYOWtugJrPYdqnKaVoIx/HDOMsTF\n" \
"JHwkNR88dp6rhonv/vKYdMtyClIs9wP5+cAMyPnxwBY2UZIodTbnCBQS3MyAbrLR\n" \
"mSfJ3LuxvZvS54o9EbCqgiire++1GEFL062f3etdTjUSc9LXq9/qOuzBf1Sgxl9X\n" \
"Vh0iuXgNBmyrAc7f26LFg6vb88mC08YIzdXfLV90RrzXGBSfjBkqvzvrQiMHPR/o\n" \
"dFZ8fyJJUbUmX1eNzBpKIcOujkGm4RxbB52W/BXko/gEzB3VSrSUA0iTMUiLN6NG\n" \
"+VLcLGYHOR9lWT1wcxT/wLPtLlReF/pWxtgnwYkWAQIDAQABo1MwUTAdBgNVHQ4E\n" \
"FgQU4yMBjJMeqcNt2zu2Vg1cXNrZ3W8wHwYDVR0jBBgwFoAU4yMBjJMeqcNt2zu2\n" \
"Vg1cXNrZ3W8wDwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAWzdA\n" \
"hLIBekyFYHX18j/sWP+Mr6RUgJpLbCLuSV+2Nast6JZpMUokhzfBLHkHoH3ixibd\n" \
"aalvWuTDxoDwFGInXvblsQ1DVFemFvx+EuX76U0IlPHSuKP3G1b+nTgVenyTOLVz\n" \
"/iTF+JN4OCOWFJfNMc73Qz2sjhaCh4MBNd/Mg0axLVBbGPGWOokWfrn4QDXPnVqV\n" \
"zW2qa7Y709jYltMtI+sRSIUL3J2qvH5ISoN1HELQkRKJDDCn4lt3glqoPCe89biK\n" \
"mnc2KCukhDocqqWUHQ==\n" \
"-----END CERTIFICATE-----\n";
;

// Copie aqui a sua chave privada do certificado do cleinte do EUGENIO (ex: xxxxx.key.pem) ▼
static const char privkey[] PROGMEM = \
"-----BEGIN PRIVATE KEY-----\n" \
"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQCmj8LwmWrIHC61\n" \
"iIUpg5a26Ams9h2qcppWgjH8cM4yxMUkfCQ1Hzx2nquGie/+8ph0y3IKUiz3A/n5\n" \
"wAzI+fHAFjZRkih1NucIFBLczIBustGZJ8ncu7G9m9Lnij0RsKqCKKt777UYQUvT\n" \
"rZ/d611ONRJz0ter3+o67MF/VKDGX1dWHSK5eA0GbKsBzt/bosWDq9vzyYLTxgjN\n" \
"1d8tX3RGvNcYFJ+MGSq/O+tCIwc9H+h0Vnx/IklRtSZfV43MGkohw66OQabhHFsH\n" \
"nZb8FeSj+ATMHdVKtJQDSJMxSIs3o0b5UtwsZgc5H2VZPXBzFP/As+0uVF4X+lbG\n" \
"2CfBiRYBAgMBAAECggEBAIN0FIsk2bSjIW4eF9JiyzEBwpkiCNm75vj9egvcz7Ab\n" \
"weeAnmbahzKrGX5uIN5agl4zLobcwiYVmlU08CIxuU07epU4P/v6X63tgdGHCJnV\n" \
"QTyZvWQbMjUN5Q7d+EKc5oUhKe3/ijJhXkHq1rAjkJkno6+LqLE6YDcvIaunk9fa\n" \
"B1TC9sgXPO74I1IT9izqJvrO+1H8yQS8B1zdsUyBydJAlTqX+ek5RnjONR9wO2+w\n" \
"zFMZfTj12CQesW1KbI/tqPf3NCz8QuFlKY7ywpNtY5ECgYEAzsZVqZWEw2Jp8J61\n" \
"y2Q2GDzDH0l0xqYQ0E3PPirvUqwO56AgsoItge7KcSt5j9wkwv5EhMHjeQaxKfL7\n" \
"1frUTI4O6vYzd+wvbtnHdVAbBDKwtu/55666VyrlbM9Nmsg25zY3tl2vZFUB6Rj4\n" \
"kkmUD4OO2BTgeSt4rkl7dTCojZUCgYEAzjatirVofqJbZDcYB4gSyNSe8mHF2qYW\n" \
"FhlDCUseFtIcOZFI0eFIoSia1mybDnj2rps5ZG3AlTw57bZkAIzV+awMM0NwcJGk\n" \
"9k+iy4uqJlLOyayepuuc87yVOo70PP+hDky9teS2nvYd+4fuxyfGdDAY5rFI2sOs\n" \
"YclPSXGck70CgYEAk3S9AgKueudjxURpQHJmYUJzo4wuyrsCoonakOrtYHdy6Zs3\n" \
"thU/frlbhPkL55uGW8gX9NSP827iSJgPH7mQTEfCO6z3Zz33VYXYx8AohAXiH5Nj\n" \
"E+V23VKp6b6sCQVeoeP4NwT4XwSAKEq2eRwfijC3XUEGE2L83M1qTVg120ECgYAE\n" \
"2HwTelfOQfprzG+gHa5zUau6flmr3aM/ObC9kypN1voa0DMp22VdhBq/VyX9nRIO\n" \
"4E7k8T9JQnUKBPMsoCKXD1fqDHej7Yg20YA90DZbWC7Lxmaj/X1erNvE2H8cv9UF\n" \
"BQCgOZOhAJ+LvZH61BBxwn+TTC8uFNMEKTrXuve28QKBgC9+jHvkX0ohap5Pq/5k\n" \
"lZlt+y0VIny0SyfklNeBpESHUoxAFSp+EbpV1EYIGw45ZJZ1IVG0ZLbkwshh/6XH\n" \
"6+hvPwqXLmgYbXo6bj8kANk7VDbmjOUGlxSLKFZ3fgnJOopB9aQeC0jdgOd7kF90\n" \
"CnUF92zx+CfKC3zknqI5VMja\n" \
"-----END PRIVATE KEY-----\n";
;

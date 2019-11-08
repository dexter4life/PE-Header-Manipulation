DWORD VAToFile(DWORD dwVirtAddr, PIMAGE_SECTION_HEADER lpSecHdr)
{
    DWORD dwReturn = dwVirtAddr;
    for(WORD wSections = 0; wSections < nSections; wSections++){
        if(dwReturn >= (dwImageBase + lpSecHdr->VirtualAddress))
        {
            if(dwReturn < (dwImageBase + lpSecHdr->VirtualAddress + lpSecHdr->Misc.VirtualSize))
            {
                dwReturn -= (dwImageBase + lpSecHdr->VirtualAddress);
                dwReturn += lpSecHdr->PointerToRawData;
                return dwReturn;
            }
        }
        lpSecHdr++;
    }
    return NULL;
}
 
DWORD FileToVA(DWORD dwFileAddr, PIMAGE_SECTION_HEADER lpSecHdr)
{
    DWORD dwReturn = dwFileAddr;
    for(WORD wSections = 0; wSections < nSections; wSections++){
        if(dwReturn >= lpSecHdr->PointerToRawData)
        {
            if(dwReturn < (lpSecHdr->PointerToRawData + lpSecHdr->SizeOfRawData))
            {
                dwReturn -= lpSecHdr->PointerToRawData;
                dwReturn += (dwImageBase + lpSecHdr->VirtualAddress);
                return dwReturn;
            }
        }
        lpSecHdr++;
    }
    return NULL;
}

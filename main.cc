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

DWORD OffsetToRVA(DWORD offset, IMAGE_SECTION_HEADER *is_hdr, unsigned scount)
{
    // Find section holding the Offset
    for(unsigned i = 0; i < scount;i++)
        if((offset >= is_hdr[i].PointerToRawData) && (offset <= is_hdr[i].PointerToRawData +is_hdr[i].SizeOfRawData))
        {
            // Convert Offset to RVA
            return offset+is_hdr[i].VirtualAddress-is_hdr[i].PointerToRawData;
        }
    return 0;
}

/*Convert Virtual Address to File Offset */
DWORD Rva2Offset(DWORD rva, PIMAGE_SECTION_HEADER psh, PIMAGE_NT_HEADERS pnt)
{
	size_t i = 0;
	PIMAGE_SECTION_HEADER pSeh;
	if (rva == 0)
	{
		return (rva);
	}
	pSeh = psh;
	for (i = 0; i < pnt->FileHeader.NumberOfSections; i++)
	{
		if (rva >= pSeh->VirtualAddress && rva < pSeh->VirtualAddress +
			pSeh->Misc.VirtualSize)
		{
			break;
		}
		pSeh++;
	}
	return (rva - pSeh->VirtualAddress + pSeh->PointerToRawData);
}

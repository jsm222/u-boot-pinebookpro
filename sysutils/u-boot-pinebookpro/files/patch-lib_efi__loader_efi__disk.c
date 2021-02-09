--- lib/efi_loader/efi_disk.c.orig	2021-02-09 17:35:56.169742000 +0100
+++ lib/efi_loader/efi_disk.c	2021-02-09 17:36:34.264396000 +0100
@@ -146,7 +146,7 @@
 	if ((uintptr_t)buffer & (this->media->io_align - 1))
 		return EFI_INVALID_PARAMETER;
 	if (lba * this->media->block_size + buffer_size >
-	    this->media->last_block * this->media->block_size)
+	    this->media->last_block * this->media->block_size + this->media->block_size)
 		return EFI_INVALID_PARAMETER;
 
 #ifdef CONFIG_EFI_LOADER_BOUNCE_BUFFER

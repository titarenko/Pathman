set AssetsArchive=Assets.paf

del %AssetsArchive%
echo.
echo Old %AssetsArchive% has been deleted.

"%ProgramFiles%\7-Zip\7z" a -tzip -r -pVidIvDiefboiljIlcofs -mem=AES256 -mx=9 %AssetsArchive% @AssetsTypes.txt -x!*.svn*

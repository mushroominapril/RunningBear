Get-ChildItem -Path . -Include *.cpp,*.h -Recurse | ForEach-Object {
    $content = Get-Content $_.FullName
    $utf8path = $_.FullName
    [System.IO.File]::WriteAllLines($utf8path, $content, [System.Text.Encoding]::UTF8)
}

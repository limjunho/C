what is procfs?
- porc file system으로 UNIX계열 OS에서 사용되며, OS의 각종 정보를 커널 모드가 아닌 유저 모드에서
쉽게 접근할 수 있도록 만들어 줌. ex) cpu사용율, 인터럽트, 네트워크 패킷 전송량, 적재된 모듈 등..

why use?
1. 파일 시스템의 오버헤드를 줄일 수 있음 - 일반적인 파일시스템은 inode와 superblocs같은
객체를 통해 관리.
2. 물리적인 파일 시스템 장치가 필요하지 않음 - proc는 커널 메모리에서 동작하는 가상 파일 시스템으로
커널에서 직접 관리.

how use?
1. Makefile과 source code가 필요. -> make를 통해 모듈 생성
2. 모듈을 적재하면 /proc디렉터리 아래에 procfile이 생성됨.
3. echo "hello world!" >> /proc/test 와 같은 터미널 명령이나 다른 프로세스에서 file io
를 이용해 write하여 proc file에 정보를 기록
4. cat /proc/test 와 같은 터미널 명령이나 다른 프로세스에서 fs를 이용해 read하여 proc file을
읽을 수 있다. 
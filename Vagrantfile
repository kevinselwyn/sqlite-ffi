Vagrant.configure("2") do |config|
  config.vm.box = "hashicorp/precise64"

  config.vm.provision "shell", inline: <<-SHELL
    sudo apt-get update
    sudo apt-get install -y make pkg-config libsqlite3-dev
    printf "\n#login directory\ncd /vagrant\n" >> /home/vagrant/.profile
  SHELL
end

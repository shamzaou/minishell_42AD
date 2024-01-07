# Use the official Debian base image
FROM debian:stable

# Debugging information
RUN echo "Debug: Before user creation" && \
    useradd -ms /bin/bash developer && \
    echo "Debug: After user creation" && \
    apt-get update && \
    echo "Debug: After apt-get update" && \
    apt-get install -y build-essential gdb openssh-server && \
    echo "Debug: After package installation"

# Set the password for the user (change 'password' to your desired password)
RUN echo 'developer:passwordy' | chpasswd

# Allow password authentication for SSH
RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# Add user to sudo group
RUN usermod -aG sudo developer

# Check SSH configuration
RUN service ssh start && \
    service ssh status

# Expose SSH port
EXPOSE 56

# Start SSH server
CMD ["/usr/sbin/sshd", "-D"]

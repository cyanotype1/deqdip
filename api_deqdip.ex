#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# GPL Licence
#------------------------------------------------------------------------
#
# Facility:
#     deqdip 
#
# Name:
#     api_deqdip.ex
#
# Description:
#     Provide an Elixir(Erlang) API implementing the deqdip decache protocol.
#
# Author:
#     marcel@aexa.uk 2020 (C)
#
# History:
#
#   Date         Name             Description
#
#   30-SEP-2011  marcel@aexa.uk   Created.
#
#
#-----------
#
#

defmodule Deqdipctl do
 @on_load :init

 def init() do
   :erlang.load_nif("./nif_deqdip", 0)
   :ok
 end

 def deqdipctl() do
  "**Advice: failed to load nif_deqdip.so"
 end


 def deqdip_proto() do

     deqdipctl()
     receive after: ( 500 -> :ok )
     deqdipctl()

  end

end



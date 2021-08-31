package volumecmds

import (
	"encoding/json"
	"pnconnector/src/log"

	"cli/cmd/displaymgr"
	"cli/cmd/globals"
	"cli/cmd/messages"
	"cli/cmd/socketmgr"

	"github.com/spf13/cobra"
)

var MountVolumeWithSubsystemCmd = &cobra.Command{
	Use:   "mount-with-subsystem [flags]",
	Short: "Create a subsystem and add listener automatically. Mount a volume to Host.",
	Long: `Create a subsystem and add listener automatically. Mount a volume to Host.

Syntax:
	mount-with-subsystem (--volume-name | -v) VolumeName (--array-name | -a) ArrayName (--subnqn | -q) SubsystemNQN (--trtype | -t) TransportType (--traddr | -i) TargetAddress (--trsvcid | -p) TransportServiceId

Example: 
	poseidonos-cli volume mount-with-subsystem --volume-name vol1 --subnqn nqn.2019-04.ibof:subsystem1 --array-name POSArray --trtype tcp --traddr 127.0.0.1 --trsvcid 1158
	
         `,
	Run: func(cmd *cobra.Command, args []string) {

		var requestList [3]messages.Request

		createSubsystemAutoParam := messages.CreateSubsystemAutoParam{
			SUBNQN: mount_volume_with_subsystem_subnqn,
		}
		createSubsystemReq := messages.Request{
			RID:     "fromfakeclient",
			COMMAND: "CREATESUBSYSTEMAUTO",
			PARAM:   createSubsystemAutoParam,
		}
		requestList[0] = createSubsystemReq

		addListenerParam := messages.AddListenerParam{
			SUBNQN:             mount_volume_with_subsystem_subnqn,
			TRANSPORTTYPE:      mount_volume_with_subsystem_trtype,
			TARGETADDRESS:      mount_volume_with_subsystem_traddr,
			TRANSPORTSERVICEID: mount_volume_with_subsystem_trsvcid,
		}
		addListenerReq := messages.Request{
			RID:     "fromCLI",
			COMMAND: "ADDLISTENER",
			PARAM:   addListenerParam,
		}
		requestList[1] = addListenerReq

		mountVolumeParam := messages.MountVolumeParam{
			VOLUMENAME: mount_volume_with_subsystem_volumeName,
			SUBNQN:     mount_volume_with_subsystem_subnqn,
			ARRAYNAME:  mount_volume_with_subsystem_arrayName,
		}
		mountVolumeReq := messages.Request{
			RID:     "fromfakeclient",
			COMMAND: "MOUNTVOLUME",
			PARAM:   mountVolumeParam,
		}
		requestList[2] = mountVolumeReq

		// Do not send request to server and print response when testing request build.
		if !(globals.IsTestingReqBld) {
			for _, request := range requestList {
				socketmgr.Connect()
				reqJSON, err := json.Marshal(request)
				if err != nil {
					log.Debug("error:", err)
				}

				displaymgr.PrintRequest(string(reqJSON))

				resJSON, err := socketmgr.SendReqAndReceiveRes(string(reqJSON))
				if err != nil {
					log.Debug("error:", err)
					return
				}
				socketmgr.Close()

				displaymgr.PrintResponse(request.COMMAND, resJSON, globals.IsDebug, globals.IsJSONRes, globals.DisplayUnit)
			}
		}
	},
}

// Note (mj): In Go-lang, variables are shared among files in a package.
// To remove conflicts between variables in different files of the same package,
// we use the following naming rule: filename_variablename. We can replace this if there is a better way.
var mount_volume_with_subsystem_volumeName = ""
var mount_volume_with_subsystem_subnqn = ""
var mount_volume_with_subsystem_arrayName = ""
var mount_volume_with_subsystem_trtype = ""
var mount_volume_with_subsystem_traddr = ""
var mount_volume_with_subsystem_trsvcid = ""

func init() {
	MountVolumeWithSubsystemCmd.Flags().StringVarP(&mount_volume_with_subsystem_volumeName, "volume-name", "v", "", "The name of the volume to mount")
	MountVolumeWithSubsystemCmd.MarkFlagRequired("volume-name")

	MountVolumeWithSubsystemCmd.Flags().StringVarP(&mount_volume_with_subsystem_subnqn, "subnqn", "q", "", "NQN of the subsystem to create")
	MountVolumeWithSubsystemCmd.MarkFlagRequired("subnqn")

	MountVolumeWithSubsystemCmd.Flags().StringVarP(&mount_volume_with_subsystem_arrayName, "array-name", "a", "", "The name of the array where the volume belongs to")
	MountVolumeWithSubsystemCmd.MarkFlagRequired("array-name")

	MountVolumeWithSubsystemCmd.Flags().StringVarP(&mount_volume_with_subsystem_trtype, "transport_type", "t", "", "NVMe-oF transport type (ex. tcp)")
	MountVolumeWithSubsystemCmd.MarkFlagRequired("transport-type")

	MountVolumeWithSubsystemCmd.Flags().StringVarP(&mount_volume_with_subsystem_traddr, "target_address", "i", "", "NVMe-oF target address (ex. 127.0.0.1)")
	MountVolumeWithSubsystemCmd.MarkFlagRequired("target_address")

	MountVolumeWithSubsystemCmd.Flags().StringVarP(&mount_volume_with_subsystem_trsvcid, "transport_service_id", "p", "", "NVMe-oF transport service id (ex. 1158)")
	MountVolumeWithSubsystemCmd.MarkFlagRequired("transport-service-id")
}
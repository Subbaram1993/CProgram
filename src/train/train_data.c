#include "train_details.h"


Train_name train[6] = {
     {12759, "CHARMINAR SF EXP", "TBM-HYB", "Sleeper"},
     {12760, "CHARMINAR SF EXP", "HYB-TBM","Sleeper"},
     {12077, "BZA JANSHATABDI","MAS-BZA", "Seating"},
     {12078, "BZA JANSHATABDI","BZA-MAS", "Seating"},
     {20677, "BZA VANDEBHARAT", "MAS-BZA","Seating"},
     {20786, "MAS VANDEBHARAT", "BZA-MAS","Seating"}
   };
Train_route_details halts[6][18] = {
     {
      {"Tambaram-TBM","N.A", "17:30", "Day-1"},
      {"Chennai Egmore-MS","18:00", "18:05", "Day-1"},
      {"Sullurpeta-SPE","19:48", "19:50", "Day-1"},
      {"Nayudupeta-NYP","20:13", "20:15", "Day-1"},
      {"Gudur-GDR","20:38", "20:40", "Day-1"},
      {"Nellore-NLR","21:08", "21:10", "Day-1"},
      {"Kavali-KVZ","21:48", "21:50", "Day-1"},
      {"Ongole-OGL","22:38", "22:40", "Day-1"},
      {"Chirala-CLX","23:18", "23:20", "Day-1"},
      {"TenaliJn-TEL","00:13", "00:15", "Day-2"},
      {"VijayawadaJn-BZA","00:50", "01:00", "Day-2"},
      {"Khammam-KMT","02:28", "02:30", "Day-2"},
      {"Mahabubabad-MABD","03:04", "03:05", "Day-2"},
      {"Warangal-WL","04:18", "04:20", "Day-2"},
      {"KazipetJn-KZJ","04:33", "04:35", "Day-2"},
      {"SecunderabadJn-SC","06:35", "06:40", "Day-2"},
      {"HyderabadDeccan-HYB","08:10", "N.A", "Day-2"}
     },
     {
      {"HyderabadDeccan-HYB","N.A","18:00","Day-1"},
      {"SecunderabadJn-SC","18:20","18:25","Day-1"},
      {"KazipetJn-KZJ","19:58","20:00","Day-1"},
      {"Warangal-WL","20:12","20:15","Day-1"},
      {"Mahabubabad-MABD","20:58","21:00","Day-1"},
      {"DornakalJn-DKJ","21:13","21:15","Day-1"},
      {"Khammam-KMT","21:38","21:40","Day-1"},
      {"VijayawadaJn-BZA","23:45","23:55","Day-1"},
      {"TenaliJn-TEL","00:18","00:20","Day-2"},
      {"Chirala-CLX","01:03","01:05","Day-2"},
      {"Ongole-OGL","01:48","01:50","Day-2"},
      {"Kavali-KVZ","02:33","02:35","Day-2"},
      {"Nellore-NLR","03:28","03:30","Day-2"},
      {"Gudur-GDR","04:08","04:10","Day-2"},
      {"Nayudupeta-NYP","04:33","04:35","Day-2"},
      {"Sullurpeta-SPE","04:53","04:55","Day-2"},
      {"Chennai Egmore-MS","06:55","07:00","Day-2"},
      {"Tambaram-TBM","08:00","N.A","Day-2"}
     },
     {
      {"Mgr Chennai Ctl-MAS", "N.A","07:15", "Day-1"},
      {"Sullurpet-SPE", "08:38","08:40", "Day-1"},
      {"Nayudupeta-NYP", "09:03","09:05", "Day-1"},
      {"Gudur-GDR", "09:23","09:25", "Day-1"},
      {"Nellore-NLR", "09:54","09:55", "Day-1"},
      {"Kavali-KVZ", "10:34","10:35", "Day-1"},
      {"Ongole-OGL", "11:24","11:25", "Day-1"},
      {"Chirala-CLX", "12:04","12:05", "Day-1"},
      {"TenaliJn-TEL", "13:09","13:10", "Day-1"},
      {"New Guntur-NGNT", "13:39","13:40", "Day-1"},
      {"VijayawadaJn-BZA", "14:55","N.A", "Day-1"}
     },
     {
      {"VijayawadaJn-BZA", "N.A","15:30", "Day-1"},
      {"New Guntur-NGNT", "16:09","16:10", "Day-1"},
      {"TenaliJn-TEL", "16:33","16:35", "Day-1"},
      {"Chirala-CLX", "17:18","17:20", "Day-1"},
      {"Ongole-OGL", "18:03","18:05", "Day-1"},
      {"Kavali-KVZ", "18:48","18:50", "Day-1"},
      {"Nellore-NLR", "19:28","19:30", "Day-1"},
      {"Gudur-GDR", "20:13","20:15", "Day-1"},
      {"Nayudupeta-NYP", "20:38","20:40", "Day-1"},
      {"Sullurpet-SPE", "21:03","21:05", "Day-1"},
      {"Mgr Chennai Ctl-MAS", "22:55","N.A", "Day-1"}
     },
     {
       {"Mgr Chennai Ctl-MAS", "N.A","05:30", "Day-1"},
       {"ReniguntaJn-RU", "07:05","07:10", "Day-1"},
       {"Nellore-NLR", "08:29","08:30", "Day-1"},
       {"Ongole-OGL", "09:43","09:45", "Day-1"},
       {"TenaliJn-TEL", "11:08","11:10", "Day-1"},
       {"VijayawadaJn-BZA", "12:10","N.A", "Day-1"}
     },
     {
       {"VijayawadaJn-BZA", "N.A","15:20", "Day-1"},
       {"TenaliJn-TEL", "15:44","15:45", "Day-1"},
       {"Ongole-OGL", "16:38","16:40", "Day-1"},
       {"Nellore-NLR", "18:04","18:05", "Day-1"},
       {"ReniguntaJn-RU", "20:05","20:10", "Day-1"},
       {"Mgr Chennai Ctl-MAS", "22:00","N.A", "Day-1"}
     }
   };

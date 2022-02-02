void playSound(bool _partyState, byte _randomSeed){
  if (_partyState == switchStatusOff)
  switch (_randomSeed) {
    case 0:
      tmrpcm.play("a.wav");
    break;
    case 1:
      tmrpcm.play("b.wav");
    break;
    case 2:
      tmrpcm.play("c.wav");
    break;
    case 3:
      tmrpcm.play("d.wav");
    break;
    case 4:
      tmrpcm.play("e.wav");
    break;
    case 5:
      tmrpcm.play("f.wav");
    break;
    case 6:
      tmrpcm.play("g.wav");
    break;
    case 7:
      tmrpcm.play("h.wav");
    break;
    case 8:
      tmrpcm.play("i.wav");
    break;
    case 9:
      tmrpcm.play("j.wav");
    break;
    case 10:
      tmrpcm.play("k.wav");
    break;
    case 11:
      tmrpcm.play("l.wav");
    break;
    case 12:
      tmrpcm.play("m.wav");
    break;
    case 13:
      tmrpcm.play("n.wav");
    break;
    case 14:
      tmrpcm.play("o.wav");
    break;
    case 15:
      tmrpcm.play("p.wav");
    break;
    case 16:
      tmrpcm.play("q.wav");
    break;
    case 17:
      tmrpcm.play("r.wav");
    break;
    case 18:
      tmrpcm.play("s.wav");
    break;
    case 19:
      tmrpcm.play("t.wav");
    break;
    case 20:
      tmrpcm.play("u.wav");
    break;
    case 21:
      tmrpcm.play("v.wav");
    break;
    default:
      tmrpcm.play("x1.wav");
   break;
  }
  else {
   _randomSeed = getRandomNumber(15);
    switch (_randomSeed){
   case 0:
      tmrpcm.play("1.wav");
    break;
    case 1:
      tmrpcm.play("2.wav");
    break;
    case 2:
      tmrpcm.play("3.wav");
    break;
    case 3:
      tmrpcm.play("4.wav");
    break;
    case 4:
      tmrpcm.play("5.wav");
    break;
    case 5:
      tmrpcm.play("6.wav");
    break;
     case 6:
      tmrpcm.play("7.wav");
    break;
     case 7:
      tmrpcm.play("8.wav");
    break;
     case 8:
      tmrpcm.play("9.wav");
    break;
     case 9:
      tmrpcm.play("10.wav");
    break;
     case 10:
      tmrpcm.play("11.wav");
    break;
     case 11:
      tmrpcm.play("12.wav");
    break;
     case 12:
      tmrpcm.play("13.wav");
    break;
     case 13:
      tmrpcm.play("14.wav");
    break;
    default:
     tmrpcm.play("3.wav");
     break;
    }
  
}
}

void playBell(){
  tmrpcm.play("x3.wav");
  eventsBeforeNextBell = 3; //Reset bell counter  
}


  //tmrpcm.stopPlayback();
  //tmrpcm.isPlaying()


//Xmas Tracks
//3 ships         a
//dingdong        b
//godrestye       c
//goodking        d
//hark            e
//wewishyouamerryxmas     f
//12days          g
//abidewithme     h
//bethlehem       i
//davidscity      j
//greensleeves    k
//hallelujah      l
//hollyandtheivy  m
//indulcijubilo   n
//ivowtothee      o
//noel            p
//ochristmastree  q
//ocomeallyefaithful  r
//odetojoy        s
//shepherds       t
//silentnight     u
//we3kings        v
//
//Pop tracks
//popcavalry      1
//poplastxmas     2
//popshakin       3
//popwish         4
//popwonderful    5
//popxmasinla     6
//popalliwant     7
//popbandaid      8
//pophollyjolly   9
//popjinglebells  10
//popmanwiththebag  11
//popsantacomingtotown    12
//popstepintoxmas   13
//popxmasmeanstome  14
//
//system tracks
//bleep01     b1
//bleep02     b2
//bleep03     b3
//bleep04     b4
//
//bell tracks
//bellLong    x1
//bellShort   x2
//peel01      x3
//peel02      x4

<template>
<div>
  <banner></banner>
  <router-view></router-view>
</div>
</template>

<script>
  import banner from './banner'
    export default {
        components:{
          banner,
        }
    }
</script>

<style scoped>

</style>
